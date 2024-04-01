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
            STATED_SENSORS,
            COMMUNICATION_SENSORS,
        };

        uint8_t state;

        uint32_t sensorsStartTime;
        uint32_t communicationSensorStartTime;

        const uint32_t sensorsStateDurtion = 40;
        const uint32_t communicationSensorStateDurtion = 100;

        float left_sensor  = 0.0;
        float front_sensor = 0.0;
        float right_sensor = 0.0;

    public:
        RobotMovil(){}
        RobotMovil(Ultrassonic &leftSensor, Ultrassonic &frontSensor, Ultrassonic &rightSensor, Communication &serial);

        void init();

        void sensors();
        void communication();
        void update();
};
#endif