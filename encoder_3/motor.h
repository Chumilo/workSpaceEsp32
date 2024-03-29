#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Encoder {
public:
    Encoder(uint8_t ch1, uint8_t ch2, uint8_t ch3, uint8_t ch4, float wheelCircumference, int encoderResolution);
    void init();
    void update();
    void calculateSpeed();
    float getSpeedLeft() const;
    float getSpeedRight() const;

private:
    struct EncoderState {
        volatile int32_t count = 0;
        volatile uint8_t lastState = 0;
    };

    uint8_t ch1, ch2, ch3, ch4;
    EncoderState leftEncoder, rightEncoder;
    float wheelCircumference;
    int encoderResolution;
    unsigned long lastUpdateTime = 0;
    float speedLeft = 0, speedRight = 0;

    static void IRAM_ATTR isrLeft();
    static void IRAM_ATTR isrRight();
    static Encoder* instance;

    void readEncoder(EncoderState &encoder, uint8_t pinA, uint8_t pinB);
    float calculateLinearSpeed(int32_t pulses, unsigned long timeElapsed);
};

#endif
