#include "motorconfig.h"
#include "motor.h"

    Encoder* Encoder::instance[2] = {nullptr, nullptr};
    
    Encoder::Encoder(uint8_t ch1, uint8_t ch2){
        this->ch1 = ch1;
        this->ch2 = ch2;

        if(!instance[0]){
          instance[0] = this;
        }
        else{
          instance[1] = this;
        }
    }
      
    void Encoder::init(){
        pinMode(ch1,INPUT);
        pinMode(ch2,INPUT);

        if(this == instance[0]){
          attachInterrupt(ch1, readRightEncoder, CHANGE);
          attachInterrupt(ch2, readRightEncoder, CHANGE);
        }
        else{
          attachInterrupt(ch1, readRightEncoder, CHANGE);
          attachInterrupt(ch2, readRightEncoder, CHANGE);
        }
    }  
    
    void Encoder::readEncoder(){
      ant = act;
      
      if (digitalRead(ch1)){
        ((act) |= (1UL << 0));
      }
      else{
        ((act) &= ~(1UL << 0));
      }
      if (digitalRead(ch2)){
        ((act) |= (1UL << 1));
      }
      else{
        ((act) &= ~(1UL << 1));
      }

      if (ant == 2 && act == 0)n++;
      if (ant == 0 && act == 1)n++;
      if (ant == 3 && act == 2)n++;
      if (ant == 1 && act == 3)n++;
    
      if (ant == 1 && act == 0)n--;
      if (ant == 3 && act == 1)n--;
      if (ant == 0 && act == 2)n--;
      if (ant == 2 && act == 3)n--;
    }

    int32_t Encoder::contEncoder()const{
      return n;
    }

    void Encoder::readRightEncoder(){
      if(instance[0]){
        instance[0]->readEncoder();
      }
    }

    void Encoder::readLeftEncoder(){
      if(instance[1]){
        instance[1]->readEncoder();
      }
    }

  
