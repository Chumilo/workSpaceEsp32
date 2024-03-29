#include "motor.h"

Encoder* Encoder::instance = nullptr;

Encoder::Encoder(uint8_t ch1, uint8_t ch2, uint8_t ch3, uint8_t ch4, float wheelCircumference, int encoderResolution)
    : ch1(ch1), ch2(ch2), ch3(ch3), ch4(ch4), wheelCircumference(wheelCircumference), encoderResolution(encoderResolution) {
    instance = this;
}

void Encoder::init() {
    pinMode(ch1, INPUT_PULLUP);
    pinMode(ch2, INPUT_PULLUP);
    pinMode(ch3, INPUT_PULLUP);
    pinMode(ch4, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(ch1), isrLeft, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ch2), isrLeft, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ch3), isrRight, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ch4), isrRight, CHANGE);
    lastUpdateTime = millis();
}

void Encoder::isrLeft() {
    if (instance) {
        instance->readEncoder(instance->leftEncoder, instance->ch1, instance->ch2);
    }
}

void Encoder::isrRight() {
    if (instance) {
        instance->readEncoder(instance->rightEncoder, instance->ch3, instance->ch4);
    }
}

void Encoder::readEncoder(EncoderState &encoder, uint8_t pinA, uint8_t pinB) {
    uint8_t state = digitalRead(pinA) | (digitalRead(pinB) << 1);
    if (state != encoder.lastState) {
        if ((encoder.lastState == 0 && state == 1) || (encoder.lastState == 1 && state == 3) ||
            (encoder.lastState == 3 && state == 2) || (encoder.lastState == 2 && state == 0)) {
            encoder.count++;
        } else if ((encoder.lastState == 1 && state == 0) || (encoder.lastState == 3 && state == 1) ||
                   (encoder.lastState == 2 && state == 3) || (encoder.lastState == 0 && state == 2)) {
            encoder.count--;
        }
        encoder.lastState = state;
    }
}

void Encoder::calculateSpeed() {
    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - lastUpdateTime;
    if (elapsedTime > 0) { // Avoid division by zero
        speedLeft = 10;calculateLinearSpeed(leftEncoder.count, elapsedTime);
        speedRight = 20;calculateLinearSpeed(rightEncoder.count, elapsedTime);
        leftEncoder.count = 0;
        rightEncoder.count = 0;
        lastUpdateTime = currentTime;
    }
}

float Encoder::calculateLinearSpeed(int32_t pulses, unsigned long timeElapsed) {
    float distance = (pulses / static_cast<float>(encoderResolution)) * wheelCircumference;
    return distance / (timeElapsed / 1000.0f); // Convert timeElapsed to seconds
}

float Encoder::getSpeedLeft() const {
    return speedLeft;
}

float Encoder::getSpeedRight() const {
    return speedRight;
}
