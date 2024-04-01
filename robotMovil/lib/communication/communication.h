#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#ifndef DATA_LENGTH
#define DATA_LENGTH 1
#endif

#ifndef COMMUNICATION_SPEED
#define COMMUNICATION_SPEED 9600
#endif

#include <Arduino.h>

class Communication
{
  private:
    String inputString = "";
    bool stringComplete = false;
    char separator = ',';
    uint8_t data[DATA_LENGTH];
    
  public:
    Communication(){}
    void init();
    uint8_t* values();
    void communicationEvent(); 
};

#endif
