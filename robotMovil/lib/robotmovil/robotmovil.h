#ifndef ROBOT_MOVIL_H
#define ROBOT_MOVIL_H

#include "communication.h"
#include "ultrassonic.h"
#include "Arduino.h"

class RobotMovil
{
    private:
        Ultrassonic leftSensor;
        Ultrassonic frontSensor;
        Ultrassonic rightSensor;

        Communication serial;

        enum robotMovilState
        {
            STATED_LEFT_SENSOR,
            STATED_FRONT_SENSOR,
            STATED_RIGHT_SENSOR,
            COMMUNICATION_SENSORS,
        };

        uint8_t state;

        uint32_t leftSensorStartTime;
        uint32_t frontSensorStartTime;
        uint32_t rightSensorStartTime;
        uint32_t communicationSensorStartTime;

        const uint32_t leftSensorStateDurtion  = 20;
        const uint32_t frontSensorStateDurtion = 20;
        const uint32_t rightSensorStateDurtion = 20;
        const uint32_t communicationSensorStateDurtion = 100;

        float left_sensor  = 0.0;
        float front_sensor = 0.0;
        float right_sensor = 0.0;

    public:
        RobotMovil(){}
        RobotMovil(Ultrassonic &leftSensor, Ultrassonic &frontSensor, Ultrassonic &rightSensor, Communication &serial);

        void init();

        void left();
        void front();
        void right();
        void communication();
        void update();
};
#endif