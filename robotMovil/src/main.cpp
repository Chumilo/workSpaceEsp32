#include "communication.h"
#include "ultrassonic.h"
#include "robotmovil.h"
#include <Arduino.h>


#define LEFT_TRIG_PIN    2
#define LEFT_ECHO_PIN    4
#define FRONT_TRIG_PIN  35
#define FRONT_ECHO_PIN  18
#define RIGHT_TRIG_PIN  34
#define RIGHT_ECHO_PIN  26

Ultrassonic leftSensor(LEFT_TRIG_PIN, LEFT_ECHO_PIN);
Ultrassonic frontSensor(FRONT_TRIG_PIN, FRONT_ECHO_PIN);
Ultrassonic rightSensor(RIGHT_TRIG_PIN, RIGHT_ECHO_PIN);

Communication serial;

RobotMovil robotMovil(leftSensor, frontSensor, rightSensor, serial);

void setup() {
  robotMovil.init();
}

void loop() {
  robotMovil.update();
}

