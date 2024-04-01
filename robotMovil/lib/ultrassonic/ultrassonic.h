#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#ifndef ALPHA
#define ALPHA 0.5
#endif

#ifndef MAX_DISTANCE
#define MAX_DISTANCE 80.0
#endif

#ifndef MIN_DISTANCE
#define MIN_DISTANCE 0.0
#endif

#include <Arduino.h>

class Ultrassonic
{
  private:  
    uint8_t trigPin;
    uint8_t echoPin;
    uint32_t duration;
    float distance = 0.0;
    float st_1 = 0.0;

  public:
    Ultrassonic(){}
    Ultrassonic(uint8_t trigPin, uint8_t echoPin);
    void init();
    float mesureDistance();
    float emaFilter(float distance, float st_1);
};

#endif
