//#include "communication.h"
//#include "ultrasonic.h"
#include "motor.h"

#//define ch1 23
#//define ch2 19
#//define ch3 27
#//define ch4 14

Motor leftMotor(1, 255, 16, 25, 17);
Motor* ptrLeftMotor = &leftMotor;

Motor rightMotor(0, 255, 5, 12, 13);
Motor* ptrRightMotor = &rightMotor; 



void setup()
{
  Serial.begin(9600);
  ptrRightMotor->init();
  ptrLeftMotor->init();

}

void loop()
{
  // uint8_t* ptrdatos = datos;
  // ptrdatos = ptrserial->valores();
  // Serial.println(String(ptrdatos[0]) + ',' + String(ptrdatos[1]) + ',' + String(ptrdatos[2]));

  //left_sensor = ptrleftSensor->mesureDistance();
  //Serial.println(String(left_sensor) + ',' + String(leftSensor.distance));
  //delay(100);

  Serial.println(String(ptrRightMotor->rightEncoder.n) + ',' +  String(ptrLeftMotor->leftEncoder.n));
  //Serial.println(String(ptrLeftMotor->leftEncoder.ch1) + ',' +  String(ptrLeftMotor->leftEncoder.ch2));

}
