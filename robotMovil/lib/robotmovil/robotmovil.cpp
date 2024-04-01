#include "robotmovil.h"

RobotMovil::RobotMovil(Ultrassonic &leftSensor, Ultrassonic &frontSensor, Ultrassonic &rightSensor, Communication &serial)
{
    this->leftSensor  = leftSensor;
    this->frontSensor = frontSensor;
    this->rightSensor = rightSensor;

    this->serial = serial;
}

void RobotMovil::init()
{
    leftSensor.init();
    frontSensor.init();
    rightSensor.init();

    serial.init();

    state = STATED_SENSORS;
    sensors();
}

void RobotMovil::sensors()
{
    left_sensor = leftSensor.mesureDistance();
    //front_sensor = frontSensor.mesureDistance();
    right_sensor = rightSensor.mesureDistance();
}

void RobotMovil::communication()
{
    Serial.println(String(left_sensor) + ',' + String(front_sensor) + ',' + String(right_sensor));
}


void RobotMovil::update()
{
    uint32_t timeNow = millis();

    switch(state){
        case STATED_SENSORS:
        {
            sensors();
            if(timeNow - sensorsStartTime > sensorsStateDurtion)
            {
                state = COMMUNICATION_SENSORS;
                sensorsStartTime = timeNow;
            }
            break;
        }

        case COMMUNICATION_SENSORS:
        {  
            communication();
            if(timeNow - communicationSensorStartTime > communicationSensorStateDurtion)
            {
                state = STATED_SENSORS;
                communicationSensorStartTime = timeNow;
            }
        }

        default:
        {
            state = STATED_SENSORS;
        }

    }
}