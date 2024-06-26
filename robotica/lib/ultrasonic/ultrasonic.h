#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#ifndef ALPHA
#define ALPHA 0.5
#endif

#include <Arduino.h>

class Ultrasonic{
  private:  
    uint8_t trigPin;
    uint8_t echoPin;
    uint32_t duration;
    float distance = 0.0;
    float st_1 = 0.0;

  public:
    //float distance = 0.0;
    Ultrasonic(){}
    Ultrasonic(uint8_t trigPin, uint8_t ecoPin);
    void init();
    float mesureDistance();
    float emaFilter(float distance, float st_1);
};
#endif