#include <Arduino.h>
#include "communicationconfig.h"
#include "communication.h"

uint8_t datos[DATA_LENGTH];
uint8_t* ptrdatos = datos;

Communication serial;

void serialEvent(){
  serial.communicationEvent();
}

void setup() {
  serial.init();
}

void loop() {
  ptrdatos = serial.values();
  Serial.println(String(ptrdatos[0]) + ',' + String(ptrdatos[1]) + ',' + String(ptrdatos[2]));
}