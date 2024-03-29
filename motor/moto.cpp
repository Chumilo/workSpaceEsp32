#include "motorconfig.h"
#include "motor.h"

    Motor* Motor::ptrRightMotor = nullptr;
    Motor* Motor::ptrLeftMotor = nullptr;

    Motor::Motor(uint8_t channel, uint8_t maxSpeed, uint8_t speedPin, uint8_t inputA, uint8_t inputB){
        this->channel = channel;
        this->maxSpeed = maxSpeed;
        this->speedPin = speedPin;
        this->inputA = inputA;
        this->inputB = inputB;
         ptrRightMotor = this;
         ptrLeftMotor =  this;
        
        rightEncoder.ch1 = RIGHT_CHUNO;
        rightEncoder.ch2 = RIGHT_CHDOS;
        leftEncoder.ch3 = LEFT_CHUNO;
        leftEncoder.ch4 = LEFT_CHDOS;
        
    }
    void Motor::init(){
        Serial.println("hola");
        pinMode(speedPin,OUTPUT);
        pinMode(inputA,OUTPUT);
        pinMode(inputB,OUTPUT);
        pinMode(rightEncoder.ch1,INPUT);
        pinMode(rightEncoder.ch2,INPUT);
        pinMode(leftEncoder.ch3,INPUT);
        pinMode(leftEncoder.ch4,INPUT);

        attachInterrupt(rightEncoder.ch1, readEncoderRight, CHANGE);
        attachInterrupt(rightEncoder.ch2, readEncoderRight, CHANGE);
        
        
        attachInterrupt(leftEncoder.ch3, readEncoderLeft, CHANGE);
        attachInterrupt(leftEncoder.ch4, readEncoderLeft, CHANGE);
        
        ledcSetup(channel,5000,8);
        ledcAttachPin(speedPin,channel);
    }
    void Motor::setSpeed(uint8_t percentage){
        uint8_t speed = (maxSpeed * percentage) / 100;
        ledcWrite(channel, speed);
    }
    void Motor::forwardMovement(){
        digitalWrite(inputA, HIGH);
        digitalWrite(inputB, LOW);
    }
    void Motor::backwardMovement(){
        digitalWrite(inputA, LOW);
        digitalWrite(inputB, HIGH);
    }
    void Motor::stopMovement(){
        digitalWrite(inputA, LOW);
        digitalWrite(inputB, LOW);
    }

    void Motor::encoderRight(){
      rightEncoder.ant = rightEncoder.act;

      if (digitalRead(rightEncoder.ch1)){
        ((rightEncoder.act) |= (1UL << 0));
      }
      else{
        ((rightEncoder.act) &= ~(1UL << 0));
      }
      if (digitalRead(rightEncoder.ch2)){
        ((rightEncoder.act) |= (1UL << 1));
      }
      else{
        ((rightEncoder.act) &= ~(1UL << 1));
      }

      if (rightEncoder.ant == 2 && rightEncoder.act == 0){
        rightEncoder.n++;
      }
      if (rightEncoder.ant == 0 && rightEncoder.act == 1){
        rightEncoder.n++;
      }
      if (rightEncoder.ant == 3 && rightEncoder.act == 2){
        rightEncoder.n++;
      }
      if (rightEncoder.ant == 1 && rightEncoder.act == 3){
        rightEncoder.n++;
      }

      if (rightEncoder.ant == 1 && rightEncoder.act == 0){
        rightEncoder.n--;
      }
      if (rightEncoder.ant == 3 && rightEncoder.act == 1){
        rightEncoder.n--;
      }
      if (rightEncoder.ant == 0 && rightEncoder.act == 2){
        rightEncoder.n--;
      }
      if (rightEncoder.ant == 2 && rightEncoder.act == 3){
        rightEncoder.n--;
      }
    }

    void Motor::encoderLeft(){
      leftEncoder.ant = leftEncoder.act;

      if (digitalRead(leftEncoder.ch3)){
        ((leftEncoder.act) |= (1UL << 0));
      }
      else{
        ((leftEncoder.act) &= ~(1UL << 0));
      }
      if (digitalRead(leftEncoder.ch4)){
        ((leftEncoder.act) |= (1UL << 1));
      }
      else{
        ((leftEncoder.act) &= ~(1UL << 1));
      }

      if (leftEncoder.ant == 2 && leftEncoder.act == 0){
        leftEncoder.n++;
      }
      if (leftEncoder.ant == 0 && leftEncoder.act == 1){
        leftEncoder.n++;
      }
      if (leftEncoder.ant == 3 && leftEncoder.act == 2){
        leftEncoder.n++;
      }
      if (leftEncoder.ant == 1 && leftEncoder.act == 3){
        leftEncoder.n++;
      }

      if (leftEncoder.ant == 1 && leftEncoder.act == 0){
        leftEncoder.n--;
      }
      if (leftEncoder.ant == 3 && leftEncoder.act == 1){
        leftEncoder.n--;
      }
      if (leftEncoder.ant == 0 && leftEncoder.act == 2){
        leftEncoder.n--;
      }
      if (leftEncoder.ant == 2 && leftEncoder.act == 3){
        leftEncoder.n--;
      }
    }

    void Motor::readEncoderRight(){
      if(ptrRightMotor != nullptr){
        ptrRightMotor->encoderRight();
      }
    }

     void Motor::readEncoderLeft(){
      if(ptrLeftMotor != nullptr){
        ptrLeftMotor->encoderLeft();
      }
    }



    
    
        
