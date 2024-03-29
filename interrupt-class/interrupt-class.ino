#include "MyClass.h"

MyClass rightMotor(19,23);
MyClass* ptrRightMotor = &rightMotor;

MyClass leftMotor(27,14);
MyClass* ptrLeftMotor = &leftMotor;


void setup() {
    Serial.begin(9600);
    ptrRightMotor->init();
    ptrLeftMotor->init(); 
}

void loop() {
    if (MyClass::interruptFlag) {
        //Serial.println("hola");
        //Serial.println(String(MyClass::n));
        MyClass::interruptFlag = 0; // Restablecer la bandera de interrupción
    }
    //Serial.println(String(ptrRightMotor->cont()));
    //Serial.println(String(ptrLeftMotor->cont()));
    Serial.println(String(ptrRightMotor->contRight()) + ',' +  String(ptrLeftMotor->contLeft()));
    //Serial.println(String(rightInstance->cont()) + ',' +  String(leftInstance->cont()));
}
