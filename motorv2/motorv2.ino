#include "motor.h"

Encoder rightEncoder(23,19);
Encoder leftEncoder(27,14);

void setup()
{
  Serial.begin(9600);
  
  rightEncoder.init();
  leftEncoder.init();
   
}

void loop()
{
  Serial.println(String(rightEncoder.contEncoder()) + ',' + String(leftEncoder.contEncoder()));
  //Serial.println(String(rightEncoder->a) + ',' + String(leftEncoder->a));
}
