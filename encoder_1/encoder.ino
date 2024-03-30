#include "encoder.h"

Encoder readEncoders(27, 14, 23, 19);
Encoder* ptrreadEncoders = &readEncoders;

void setup() {
    Serial.begin(9600);
    readEncoders.init();
}
 
void loop() {
    Serial.println(String(ptrreadEncoders->counterLeft()) + ',' + String(ptrreadEncoders->counterRight()));
}
