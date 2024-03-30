#include <Arduino.h>
#include "encoder.h"

Encoder readEncoders(27, 14, 23, 19);

void setup() 
{
  Serial.begin(9600);
  readEncoders.init();  
}
 
void loop() 
{
 readEncoders.calculateSpeed();
 Serial.println(String(readEncoders.speedLeft()) + ',' + String(readEncoders.speedRight()));
 delay(100);
}