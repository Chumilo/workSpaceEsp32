#include "ultrassonic.h"

Ultrassonic::Ultrassonic(uint8_t trigPin, uint8_t echoPin)
{
  this->trigPin = trigPin;
  this->echoPin = echoPin;
}

void Ultrassonic::init()
{
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
}

float Ultrassonic::mesureDistance()
{
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin,HIGH);
  st_1 = distance;
  distance = 0.017 * duration;
  if(distance >= MAX_DISTANCE)
  {
    distance = MAX_DISTANCE;
  }
  if(distance <= MIN_DISTANCE)
  {
    distance = MIN_DISTANCE;
  }
  return emaFilter(distance,st_1);
}

float Ultrassonic::emaFilter(float dsitance, float st_1)
{
  return (ALPHA * distance) + ((1.0 - ALPHA) * st_1);
}
