#include <cmath>

//
// Created by Florian Bruggisser on 21.11.18.
//

#include <util/MathUtils.h>
#include "HSVColor.h"

HSVColor::HSVColor() : HSVColor(0.0f, 0.0f, 0.0f) {

}

HSVColor::HSVColor(float hue, float saturation, float value) {
    this->h = hue;
    this->s = saturation;
    this->v = value;
}

HSVColor HSVColor::shift(float dh, float ds, float dv) {
    float hue = static_cast<int>(std::llround(getH() + dh) % 360);

    return {hue,
            MathUtils::limit(getS() + ds, 0.0f, 1.0f),
            MathUtils::limit(getV() + dv, 0.0f, 1.0f)};
}

float HSVColor::getH() const {
    return h;
}

float HSVColor::getS() const {
    return s;
}

float HSVColor::getV() const {
    return v;
}
