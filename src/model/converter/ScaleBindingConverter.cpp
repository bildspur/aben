//
// Created by Florian Bruggisser on 01.01.19.
//

#include <Arduino.h>
#include "ScaleBindingConverter.h"

ScaleBindingConverter::ScaleBindingConverter(float scale, bool roundValue) {
    this->scale = scale;
    this->roundValue = roundValue;
}


float ScaleBindingConverter::convertInput(float value) {
    auto result = value * scale;

    if (roundValue)
        return llroundf(result);

    return result;
}

float ScaleBindingConverter::convertOutput(float value) {
    auto result = value / scale;

    if (roundValue)
        return llroundf(result);

    return result;
}

float ScaleBindingConverter::getScale() const {
    return scale;
}

void ScaleBindingConverter::setScale(float scale) {
    ScaleBindingConverter::scale = scale;
}

bool ScaleBindingConverter::isRoundValue() const {
    return roundValue;
}

void ScaleBindingConverter::setRoundValue(bool roundValue) {
    ScaleBindingConverter::roundValue = roundValue;
}
