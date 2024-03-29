#include "motor.h"

Encoder* Encoder::ptrRightEncoder = nullptr;
Encoder* Encoder::ptrLeftEncoder = nullptr;

volatile int32_t countLeft = 0;
volatile int32_t countRight = 0;
volatile uint8_t antRight = 0;
volatile uint8_t antLeft = 0;
volatile uint8_t actRight = 0;
volatile uint8_t actLeft = 0;

Encoder::Encoder(uint8_t ch1, uint8_t ch2, uint8_t ch3, uint8_t ch4){
        this->ch1 = ch1;
        this->ch2 = ch2;
        this->ch3 = ch3;
        this->ch4 = ch4;
        ptrRightEncoder = this;
        ptrLeftEncoder = this;
}

void Encoder::init() {
    pinMode(ch1, INPUT);
    pinMode(ch2, INPUT);
    attachInterrupt(digitalPinToInterrupt(ch1), ISR_Left, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ch2), ISR_Left, CHANGE);

    pinMode(ch3, INPUT);
    pinMode(ch4, INPUT);
    attachInterrupt(digitalPinToInterrupt(ch3), ISR_Right, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ch4), ISR_Right, CHANGE);
}

void Encoder::ISR_Left() {
    ptrLeftEncoder->readLeftEncoder();
}

void Encoder::ISR_Right() {
    ptrRightEncoder->readRightEncoder();
}

void Encoder::readLeftEncoder(){
  antLeft = actLeft;
  if (digitalRead(ch1)){
    ((actLeft) |= (1UL << 0));
  }
  else{
    ((actLeft) &= ~(1UL << 0));
  }
  if (digitalRead(ch2)){
    ((actLeft) |= (1UL << 1));
  }
  else{
    ((actLeft) &= ~(1UL << 1));
  }
  if (antLeft == 2 && actLeft == 0)countLeft++;
  if (antLeft == 0 && actLeft == 1)countLeft++;
  if (antLeft == 3 && actLeft == 2)countLeft++;
  if (antLeft == 1 && actLeft == 3)countLeft++;

  if (antLeft == 1 && actLeft == 0)countLeft--;
  if (antLeft == 3 && actLeft == 1)countLeft--;
  if (antLeft == 0 && actLeft == 2)countLeft--;
  if (antLeft == 2 && actLeft == 3)countLeft--;
}

int32_t Encoder::counterLeft(){
  return countLeft;
 }

void Encoder::readRightEncoder(){
   antRight = actRight;
  if (digitalRead(ch3)){
    ((actRight) |= (1UL << 0));
  }
  else{
    ((actRight) &= ~(1UL << 0));
  }
  if (digitalRead(ch4)){
    ((actRight) |= (1UL << 1));
  }
  else{
    ((actRight) &= ~(1UL << 1));
  }
  if (antRight == 2 && actRight == 0)countRight++;
  if (antRight == 0 && actRight == 1)countRight++;
  if (antRight == 3 && actRight == 2)countRight++;
  if (antRight == 1 && actRight == 3)countRight++;

  if (antRight == 1 && actRight == 0)countRight--;
  if (antRight == 3 && actRight == 1)countRight--;
  if (antRight == 0 && actRight == 2)countRight--;
  if (antRight == 2 && actRight == 3)countRight--;
 }

 int32_t Encoder::counterRight(){
  return countRight;
 }
