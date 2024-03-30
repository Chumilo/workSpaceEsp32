#include "config.h"
#include "communication.h"

void Communication::init()
{
  Serial.begin(COMMUNICATION_SPEED);
}

uint8_t* Communication::values()
{
  if(stringComplete)
  { 
    for(uint8_t i=0; i<DATA_LENGTH; i++)
    { 
      uint8_t index = inputString.indexOf(separator);     
      data[i] = inputString.substring(0,index).toInt();      
      inputString = inputString.substring(index + 1);
    }  
    inputString = "";
    stringComplete = false;
  }
  return data;
}
    
void Communication::communicationEvent()
{
  while(Serial.available())
  {
    char inChar = (char)Serial.read();
    inputString += inChar;  
    if(inChar == '\n')
    {
      stringComplete = true;
    }
  }
}
