#include "communication.h"
#include "ultrasonic.h"
#include "motor.h"

#define ch1 23
#define ch2 19
#define ch3 27
#define ch4 14

uint8_t datos[DATA_LENGTH];
float left_sensor = 0.0;

Communication serial;
Communication *ptrserial = &serial;

Ultrasonic leftSensor(2, 4);
Ultrasonic *ptrleftSensor = &leftSensor;

Motor rightMotor(0, 255, 5, 12, 13);
Motor leftMotor(1, 255, 16, 25, 17);

Encoder rightEncoder;
Encoder leftEncoder;

void serialEvent()
{
  serial.communicationEvent();
}

void IRAM_ATTR EncoderR()
{
  rightEncoder.ant = rightEncoder.act;

  if (digitalRead(ch1))
    //bitSet(rightEncoder.act, 0);
    ((rightEncoder.act) |= (1UL << 0));
  else
    //bitClear(rightEncoder.act, 0);
    ((rightEncoder.act) &= ~(1UL << 0));
  if (digitalRead(ch2))
    //bitSet(rightEncoder.act, 1);
    ((rightEncoder.act) |= (1UL << 1));
  else
    //bitClear(rightEncoder.act, 1);
    ((rightEncoder.act) &= ~(1UL << 1));

  if (rightEncoder.ant == 2 && rightEncoder.act == 0)
    rightEncoder.n++;
  if (rightEncoder.ant == 0 && rightEncoder.act == 1)
    rightEncoder.n++;
  if (rightEncoder.ant == 3 && rightEncoder.act == 2)
    rightEncoder.n++;
  if (rightEncoder.ant == 1 && rightEncoder.act == 3)
    rightEncoder.n++;

  if (rightEncoder.ant == 1 && rightEncoder.act == 0)
    rightEncoder.n--;
  if (rightEncoder.ant == 3 && rightEncoder.act == 1)
    rightEncoder.n--;
  if (rightEncoder.ant == 0 && rightEncoder.act == 2)
    rightEncoder.n--;
  if (rightEncoder.ant == 2 && rightEncoder.act == 3)
    rightEncoder.n--;
}

void IRAM_ATTR EncoderL()
{
  leftEncoder.ant = leftEncoder.act;

  if (digitalRead(ch3))
    bitSet(leftEncoder.act, 0);
  else
    bitClear(leftEncoder.act, 0);
  if (digitalRead(ch4))
    bitSet(leftEncoder.act, 1);
  else
    bitClear(leftEncoder.act, 1);

  if (leftEncoder.ant == 2 && leftEncoder.act == 0)
    leftEncoder.n++;
  if (leftEncoder.ant == 0 && leftEncoder.act == 1)
    leftEncoder.n++;
  if (leftEncoder.ant == 3 && leftEncoder.act == 2)
    leftEncoder.n++;
  if (leftEncoder.ant == 1 && leftEncoder.act == 3)
    leftEncoder.n++;

  if (leftEncoder.ant == 1 && leftEncoder.act == 0)
    leftEncoder.n--;
  if (leftEncoder.ant == 3 && leftEncoder.act == 1)
    leftEncoder.n--;
  if (leftEncoder.ant == 0 && leftEncoder.act == 2)
    leftEncoder.n--;
  if (leftEncoder.ant == 2 && leftEncoder.act == 3)
    leftEncoder.n--;
}

void setup()
{
  ptrserial->init();
  ptrleftSensor->init();

  
  pinMode(ch1, INPUT);
  pinMode(ch2, INPUT);
  pinMode(ch3, INPUT);
  pinMode(ch4, INPUT);

  attachInterrupt(ch1, EncoderR, CHANGE);
  attachInterrupt(ch2, EncoderR, CHANGE);

  attachInterrupt(ch3, EncoderL, CHANGE);
  attachInterrupt(ch4, EncoderL, CHANGE);
}

void loop()
{
  // uint8_t* ptrdatos = datos;
  // ptrdatos = ptrserial->valores();
  // Serial.println(String(ptrdatos[0]) + ',' + String(ptrdatos[1]) + ',' + String(ptrdatos[2]));

  //left_sensor = ptrleftSensor->mesureDistance();
  //Serial.println(String(left_sensor) + ',' + String(leftSensor.distance));
  //delay(100);

  Serial.println(String(1UL));
}
