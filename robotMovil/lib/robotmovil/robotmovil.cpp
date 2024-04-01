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

    state = STATED_LEFT_SENSOR;
    left();
}

void RobotMovil::left()
{
    left_sensor = leftSensor.mesureDistance();
                             
}

void RobotMovil::front()
{
    front_sensor = frontSensor.mesureDistance();
}

void RobotMovil::right()
{
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
        case STATED_LEFT_SENSOR:
        {
            left();
            if(timeNow - leftSensorStartTime > leftSensorStateDurtion)
            {
                state = STATED_FRONT_SENSOR;
                leftSensorStartTime = timeNow;
            }
            break;
        }

        case STATED_FRONT_SENSOR:
        {
            if(timeNow - frontSensorStartTime > frontSensorStateDurtion)
            {
                state = STATED_RIGHT_SENSOR;
                frontSensorStartTime = timeNow;
            }
            break;
        }

        case STATED_RIGHT_SENSOR:
        {
            if(timeNow - rightSensorStartTime > rightSensorStateDurtion)
            {
                state = COMMUNICATION_SENSORS;
                rightSensorStartTime = timeNow;
            }
            break;
        }

        case COMMUNICATION_SENSORS:
        {  
            communication();
            if(timeNow - communicationSensorStartTime > communicationSensorStateDurtion)
            {
                state = STATED_LEFT_SENSOR;
                communicationSensorStartTime = timeNow;
            }
        }

        default:
        {
            state = STATED_LEFT_SENSOR;
        }

    }
}