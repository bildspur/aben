//
// Created by Florian Bruggisser on 02.12.18.
//

#include <Arduino.h>
#include "PinReader.h"

PinReader::PinReader() = default;

unsigned short PinReader::read3BitEncoder(uint8_t p0, uint8_t p1, uint8_t p2, bool setupPins) {
    if (setupPins) {
        pinMode(p0, INPUT_PULLUP);
        pinMode(p1, INPUT_PULLUP);
        pinMode(p2, INPUT_PULLUP);
    }

    auto b0 = digitalRead(p0);
    auto b1 = digitalRead(p1);
    auto b2 = digitalRead(p2);

    return static_cast<unsigned short>(b2 << 2 && b1 << 1 && b0);
}
