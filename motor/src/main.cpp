#include <Arduino.h>
#include "motor.h"

Motor leftMotor(1, 255, 16, 25, 17);
Motor rightMotor(0, 255, 5, 12, 13);




void setup()
{
  Serial.begin(9600);
  leftMotor.init();
  rightMotor.init();
}

void loop()
{
  leftMotor.setSpeed(50);
  rightMotor.setSpeed(50);
  leftMotor.moveForward();
  rightMotor.moveForward();
  delay(1000);
  leftMotor.moveBackward();
  rightMotor.moveBackward();
  delay(1000);
  leftMotor.setSpeed(0);
  rightMotor.setSpeed(0);
  leftMotor.stop();
  rightMotor.stop();
}
