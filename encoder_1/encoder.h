#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

class Encoder {
private:
    
    volatile uint8_t antRight;
    volatile uint8_t antLeft;
    volatile uint8_t actRight;
    volatile uint8_t actLeft;
    volatile int32_t countRight;
    volatile int32_t countLeft;
    uint8_t ch1;
    uint8_t ch2;
    uint8_t ch3;
    uint8_t ch4;

    static Encoder* ptrRightEncoder;
    static Encoder* ptrLeftEncoder;

public:
    Encoder(){}   
    Encoder(uint8_t ch1, uint8_t ch2, uint8_t ch3, uint8_t ch4);
    void init();
    static void ISR_Left();
    static void ISR_Right();
    void readRightEncoder();
    void readLeftEncoder();
    int32_t counterRight();
    int32_t counterLeft();
};

#endif // MOTOR_H
