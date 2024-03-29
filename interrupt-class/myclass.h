#ifndef MYCLASS_H
#define MYCLASS_H

#include <Arduino.h>

class MyClass {
private:
    volatile uint8_t ant;
    volatile uint8_t act;
    volatile uint8_t ch1;
    volatile uint8_t ch2;
    volatile int32_t nRight;
    volatile int32_t nLeft;
    void encoderRight();
    void encoderLeft();
    static void myInterruptHandlerRight();
    static void myInterruptHandlerLeft();

    static MyClass* ptrRightMotor;
    static MyClass* ptrLeftMotor;
    
public:
    MyClass(){}
    MyClass(uint8_t ch1, uint8_t ch2);
    static volatile int interruptFlag;
    
    
    void init();
    
    int32_t contRight();

    int32_t contLeft();
};

#endif
