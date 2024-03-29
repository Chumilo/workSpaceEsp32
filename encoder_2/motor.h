#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Encoder {
private:
    struct EncoderState{
      volatile uint8_t Ant;
      volatile uint8_t Act;
      volatile int32_t Count;
      volatile float V;
    };
    
    uint8_t ch1;
    uint8_t ch2;
    uint8_t ch3;
    uint8_t ch4;

    static Encoder* ptrRightEncoder;
    static Encoder* ptrLeftEncoder;

    EncoderState left;
    EncoderState right;
 

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
