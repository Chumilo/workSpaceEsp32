#include "motor.h"

Encoder readEncoders(27, 14, 23, 19);
Encoder* ptrreadEncoders = &readEncoders;

void setup() {
    Serial.begin(9600);
    readEncoders.init();
    
}
 
void loop() {
 readEncoders.calculateSpeed();
 Serial.println(String(ptrreadEncoders->speedLeft()) + ',' + String(ptrreadEncoders->speedRight()));
 delay(100);
}
