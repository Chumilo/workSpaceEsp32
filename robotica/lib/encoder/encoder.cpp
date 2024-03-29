#include "encoder.h"

Encoder* Encoder::ptrRightEncoder = nullptr;
Encoder* Encoder::ptrLeftEncoder = nullptr;

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
  
  lastUpdateTime = millis();
}

void Encoder::ISR_Left() {
  ptrLeftEncoder->readLeftEncoder();
}

void Encoder::ISR_Right() {
  ptrRightEncoder->readRightEncoder();
}

void Encoder::readLeftEncoder(){
  left.Ant = left.Act;
  if (digitalRead(ch1)){
    ((left.Act) |= (1UL << 0));
  }
  else{
    ((left.Act) &= ~(1UL << 0));
  }
  if (digitalRead(ch2)){
    ((left.Act) |= (1UL << 1));
  }
  else{
    ((left.Act) &= ~(1UL << 1));
  }
  if (left.Ant == 2 && left.Act == 0)left.Count++;
  if (left.Ant == 0 && left.Act == 1)left.Count++;
  if (left.Ant == 3 && left.Act == 2)left.Count++;
  if (left.Ant == 1 && left.Act == 3)left.Count++;

  if (left.Ant == 1 && left.Act == 0)left.Count--;
  if (left.Ant == 3 && left.Act == 1)left.Count--;
  if (left.Ant == 0 && left.Act == 2)left.Count--;
  if (left.Ant == 2 && left.Act == 3)left.Count--;
}

void Encoder::readRightEncoder(){
    right.Ant = right.Act;
    if (digitalRead(ch3)){
        ((right.Act) |= (1UL << 0));
    }
    else{
        ((right.Act) &= ~(1UL << 0));
    }
    if (digitalRead(ch4)){
        ((right.Act) |= (1UL << 1));
    }
    else{
        ((right.Act) &= ~(1UL << 1));
    }

    if (right.Ant == 2 && right.Act == 0)right.Count++;
    if (right.Ant == 0 && right.Act == 1)right.Count++;
    if (right.Ant == 3 && right.Act == 2)right.Count++;
    if (right.Ant == 1 && right.Act == 3)right.Count++;

    if (right.Ant == 1 && right.Act == 0)right.Count--;
    if (right.Ant == 3 && right.Act == 1)right.Count--;
    if (right.Ant == 0 && right.Act == 2)right.Count--;
    if (right.Ant == 2 && right.Act == 3)right.Count--;
}

void Encoder::calculateSpeed() {
    uint32_t currentTime = millis();
    uint32_t elapsedTime = currentTime - lastUpdateTime;
      
    if (elapsedTime > 0) { 
        left.Speed = calculateLinearSpeed(left.Count, elapsedTime);
        right.Speed = calculateLinearSpeed(right.Count, elapsedTime);
        left.Count = 0;
        right.Count = 0;
        lastUpdateTime = currentTime;
    }
}

float Encoder::calculateLinearSpeed(volatile int32_t pulses, uint32_t timeElapsed) {
    float velocity = (pulses * 0.0618) / timeElapsed;
    return velocity;
}

float Encoder::speedLeft(){
    return left.Speed; 
}

float Encoder::speedRight(){
    return right.Speed; 
}

 