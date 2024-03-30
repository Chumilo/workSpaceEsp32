#include "motor.h"

Motor::Motor(uint8_t channel, uint8_t maxPwm, uint8_t speedPin, uint8_t inputA, uint8_t inputB)
{
  this->channel = channel;
  this->maxPwm = maxPwm;
  this->speedPin = speedPin;
  this->inputA = inputA;
  this->inputB = inputB;
}

void Motor::init()
{
  pinMode(speedPin, OUTPUT);
  pinMode(inputA, OUTPUT);
  pinMode(inputB, OUTPUT);

  ledcSetup(channel, 5000, 8);
  ledcAttachPin(speedPin, channel);
}

void Motor::setSpeed(uint8_t percentage)
{
  speed = (maxPwm * percentage) / 100;
  ledcWrite(channel, speed);
}

void Motor::moveForward()
{
  digitalWrite(inputA, HIGH);
  digitalWrite(inputB, LOW);
}

void Motor::moveBackward()
{
  digitalWrite(inputA, LOW);
  digitalWrite(inputB, HIGH);
}

void Motor::stop()
{
  digitalWrite(inputA, LOW);
  digitalWrite(inputB, LOW);
}
   
      
    