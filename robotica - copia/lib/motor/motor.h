#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor
{
private:
    uint8_t channel;
    uint8_t maxSpeed;
    uint8_t speedPin;
    uint8_t inputA;
    uint8_t inputB;

public:
    Motor() {}
    Motor(uint8_t channel, uint8_t maxSpeed, uint8_t speedPin, uint8_t inputA, uint8_t inputB);
    void init();
    void setSpeed(uint8_t percentage);
    void forwardMovement();
    void backwardMovement();
    void stopMovement();
};

typedef struct
{
    volatile int32_t n = 0;
    volatile uint8_t ant = 0;
    volatile uint8_t act = 0;
    float linealSpeed = 0.0;
} Encoder;

#endif