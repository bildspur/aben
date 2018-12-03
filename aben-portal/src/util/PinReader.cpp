//
// Created by Florian Bruggisser on 02.12.18.
//

#include <Arduino.h>
#include "PinReader.h"

PinReader::PinReader() = default;

unsigned short PinReader::read3BitEncoder(uint8_t p0, uint8_t p1, uint8_t p2, bool setupPins) {
    if (setupPins) {
        pinMode(p0, INPUT_PULLDOWN_16);
        pinMode(p1, INPUT_PULLDOWN_16);
        pinMode(p2, INPUT_PULLDOWN_16);
    }

    auto b0 = digitalRead(p0);
    auto b1 = digitalRead(p1);
    auto b2 = digitalRead(p2);

    Serial.printf("Portal: B0=%d B1=%d B2=%d\n", b0, b1, b2);

    return static_cast<unsigned short>(b2 << 2 & b1 << 1 & b0);
}
