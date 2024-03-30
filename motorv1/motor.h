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
    
    void encoderRight();
    static void readEncoderRight();
    static Motor* ptrRightMotor;

    void encoderLeft();
    static void readEncoderLeft();
    static Motor* ptrLeftMotor;

public:
    Motor() {}
    Motor(uint8_t channel, uint8_t maxSpeed, uint8_t speedPin, uint8_t inputA, uint8_t inputB);
    void init();
    void setSpeed(uint8_t percentage);
    void forwardMovement();
    void backwardMovement();
    void stopMovement();

   
    typedef struct
    {
    volatile int32_t n = 0;
    volatile uint8_t ant = 0;
    volatile uint8_t act = 0;
    uint8_t ch1;
    uint8_t ch2;
    uint8_t ch3;
    uint8_t ch4;
    } Encoder;
    Encoder rightEncoder;
    Encoder leftEncoder;
};

#endif
