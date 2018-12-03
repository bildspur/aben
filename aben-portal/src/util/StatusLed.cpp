//
// Created by Florian Bruggisser on 19.11.18.
//

#include <Arduino.h>
#include "StatusLed.h"

uint8_t StatusLed::ledPin;

bool StatusLed::blinking;

uint8_t StatusLed::brightness;

void StatusLed::setup(uint8_t ledPin) {
    StatusLed::ledPin = ledPin;

    pinMode(StatusLed::ledPin, OUTPUT);
    turnOff();
}

void StatusLed::loop() {

}

void StatusLed::turnOn() {
    //setBrightness(255);
    digitalWrite(ledPin, LOW);
}

void StatusLed::turnOff() {
    //setBrightness(0);
    digitalWrite(ledPin, HIGH);
}

void StatusLed::setBrightness(uint8_t brightness) {
    StatusLed::brightness = brightness;
    analogWrite(ledPin, 255 - brightness);
}

void StatusLed::ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax) {
    auto v = (value > valueMax) ? valueMax : value;

    // calculate duty, 8191 from 2 ^ 13 - 1
    uint32_t duty = (8191 / valueMax) * v;

    // write duty to LEDC
    //ledcWrite(channel, duty);
}
