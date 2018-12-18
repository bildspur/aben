//
// Created by Florian Bruggisser on 18.12.18.
//

#include <util/MathUtils.h>
#include "MSBindingConverter.h"

float MSBindingConverter::convertInput(float value) {
    return MathUtils::secondsToMillis(static_cast<unsigned long>(value));
}

float MSBindingConverter::convertOutput(float value) {
    return MathUtils::millisToSeconds(static_cast<unsigned long>(value));
}
