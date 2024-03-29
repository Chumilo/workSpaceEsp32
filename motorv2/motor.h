#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Encoder
{
private:
   volatile int32_t n = 0;
   volatile uint8_t ant = 0;
   volatile uint8_t act = 0;
   uint8_t ch1;
   uint8_t ch2;
   static Encoder* instance[2];
   void readEncoder();
    
public:
    Encoder() {}
    Encoder(uint8_t ch1, uint8_t ch2);
   ~Encoder(){};
    void init();
    int32_t contEncoder() const;
    static void readRightEncoder();
    static void readLeftEncoder();
};

#endif
