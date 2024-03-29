#include "motor.h"

    Motor::Motor(uint8_t channel, uint8_t maxSpeed, uint8_t speedPin, uint8_t inputA, uint8_t inputB){
        this->channel = channel;
        this->maxSpeed = maxSpeed;
        this->speedPin = speedPin;
        this->inputA = inputA;
        this->inputB = inputB;
    }

    void Motor::init(){
        pinMode(speedPin,OUTPUT);
        pinMode(inputA,OUTPUT);
        pinMode(inputB,OUTPUT);
       
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

  