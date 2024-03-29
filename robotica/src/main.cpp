#include "communication.h"
#include "ultrasonic.h"
#include "motor.h"
#include "encoder.h"

#define ch1 23
#define ch2 19
#define ch3 27
#define ch4 14

uint8_t datos[DATA_LENGTH];
float left_sensor = 0.0;

Communication serial;
Communication* ptrserial = &serial;

Ultrasonic leftSensor(2,4);
Ultrasonic* ptrLeftSensor = &leftSensor;

//Motor rightMotor(0, 255, 5, 12, 13);
//Motor* ptrRightMotor = &rightMotor; 

//Motor leftMotor(1, 255, 16, 25, 17);
//Motor* ptrLeftMotor = &leftMotor;

//Encoder readEncoders(27, 14, 23, 19);
//Encoder* ptrreadEncoders = &readEncoders;



void serialEvent()
{
  serial.communicationEvent();
}


void setup()
{
  ptrserial->init();
  //ptrLeftSensor->init();
  leftSensor.init();
  //ptrLeftMotor->init();
  //ptrRightMotor->init();
  //readEncoders.init();
}

void loop()
{
  // uint8_t* ptrdatos = datos;
  // ptrdatos = ptrserial->valores();
  // Serial.println(String(ptrdatos[0]) + ',' + String(ptrdatos[1]) + ',' + String(ptrdatos[2]));

  //left_sensor = ptrLeftSensor->mesureDistance();
  //Serial.println(String(left_sensor) + ',' + String(leftSensor.distance));
  Serial.println(String(leftSensor.mesureDistance()));
  delay(100);

  //readEncoders.calculateSpeed();
  //Serial.println(String(ptrreadEncoders->speedLeft()) + ',' + String(ptrreadEncoders->speedRight()));
  //delay(100);

}
