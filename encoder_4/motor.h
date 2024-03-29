#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Encoder {
private:
    struct EncoderState{
      volatile uint8_t Ant;
      volatile uint8_t Act;
      volatile int32_t Count;
      volatile float Speed;
    };
    
    uint8_t ch1;
    uint8_t ch2;
    uint8_t ch3;
    uint8_t ch4;

    static Encoder* ptrRightEncoder;
    static Encoder* ptrLeftEncoder;

    EncoderState left;
    EncoderState right;

    uint32_t lastUpdateTime = 0;
    //float speedLeft = 0; 
    //float speedRight = 0;

    
 
public:
    Encoder(){}   
    Encoder(uint8_t ch1, uint8_t ch2, uint8_t ch3, uint8_t ch4);
    void init();
    static void ISR_Left();
    static void ISR_Right();
    void readRightEncoder();
    void readLeftEncoder();
    float speedRight();
    float speedLeft();
    void calculateSpeed();
    float calculateLinearSpeed(int32_t pulses, uint32_t timeElapsed);
    int8_t a = 0;
    
};

#endif // MOTOR_H
