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
    return {
            MathUtils::limit(h + dh, 0.0f, 1.0f),
            MathUtils::limit(s + ds, 0.0f, 1.0f),
            MathUtils::limit(v + dv, 0.0f, 1.0f)
    };
}
