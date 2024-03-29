#include "MyClass.h"

volatile int MyClass::interruptFlag = 0;
//volatile int32_t MyClass::n = 0;

//volatile uint8_t MyClass::ant = 0;
//volatile uint8_t MyClass::act = 0;

//volatile uint8_t MyClass::ch1;
//volatile uint8_t MyClass::ch2;

MyClass* MyClass::ptrRightMotor = nullptr;
MyClass* MyClass::ptrLeftMotor = nullptr;

MyClass::MyClass(uint8_t ch1, uint8_t ch2){
  this->ch1 = ch1;
  this->ch2 = ch2;
  ptrRightMotor = this;
  ptrLeftMotor =  this;
  //n = 0;
}

void MyClass::encoderRight(){
  ant = act;
  if (digitalRead(ch1)){
    ((act) |= (1UL << 0));
  }
  else{
    ((act) &= ~(1UL << 0));
  }
  if (digitalRead(ch2)){
    ((act) |= (1UL << 1));
  }
  else{
    ((act) &= ~(1UL << 1));
  }

  if (ant == 2 && act == 0)nRight++;
  if (ant == 0 && act == 1)nRight++;
  if (ant == 3 && act == 2)nRight++;
  if (ant == 1 && act == 3)nRight++;

  if (ant == 1 && act == 0)nRight--;
  if (ant == 3 && act == 1)nRight--;
  if (ant == 0 && act == 2)nRight--;
  if (ant == 2 && act == 3)nRight--;
  //Serial.println(String(n));
}

void MyClass::encoderLeft(){
  ant = act;
  if (digitalRead(ch1)){
    ((act) |= (1UL << 0));
  }
  else{
    ((act) &= ~(1UL << 0));
  }
  if (digitalRead(ch2)){
    ((act) |= (1UL << 1));
  }
  else{
    ((act) &= ~(1UL << 1));
  }

  if (ant == 2 && act == 0)nLeft++;
  if (ant == 0 && act == 1)nLeft++;
  if (ant == 3 && act == 2)nLeft++;
  if (ant == 1 && act == 3)nLeft++;

  if (ant == 1 && act == 0)nLeft--;
  if (ant == 3 && act == 1)nLeft--;
  if (ant == 0 && act == 2)nLeft--;
  if (ant == 2 && act == 3)nLeft--;
  //Serial.println(String(n));
}

void MyClass::myInterruptHandlerRight() {
    if(ptrRightMotor != nullptr){
      ptrRightMotor->encoderRight();
    }
    //n=1;
    interruptFlag = 1;
    //Serial.println(String(MyClass::n));
}

void MyClass::myInterruptHandlerLeft() {
    if(ptrLeftMotor != nullptr){
      ptrLeftMotor->encoderLeft();
    }
}

int32_t MyClass::contRight(){
  return nRight;
}

int32_t MyClass::contLeft(){
  return nLeft;
}

void MyClass::init(){
  pinMode(ch1, INPUT);
  pinMode(ch2, INPUT);
  if(this == ptrRightMotor){
    attachInterrupt(ch1, myInterruptHandlerRight, CHANGE);
    attachInterrupt(ch2, myInterruptHandlerRight, CHANGE);
  }
  else if(this == ptrLeftMotor){
    attachInterrupt(ch1, myInterruptHandlerLeft, CHANGE);
    attachInterrupt(ch2, myInterruptHandlerLeft, CHANGE);
  }
}
