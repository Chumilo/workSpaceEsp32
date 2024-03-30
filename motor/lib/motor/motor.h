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
        uint8_t speed;
   
    
    public:
        Motor() {}
        Motor(uint8_t channel, uint8_t maxSpeed, uint8_t speedPin, uint8_t inputA, uint8_t inputB);
        void init();
        void setSpeed(uint8_t percentage);
        void moveForward();
        void moveBackward();
        void stop();
};

#endif
