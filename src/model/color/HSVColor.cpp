//
// Created by Florian Bruggisser on 21.11.18.
//

#include "HSVColor.h"

HSVColor::HSVColor() : HSVColor(0.0f, 0.0f, 0.0f) {

}

HSVColor::HSVColor(float hue, float saturation, float value) {
    this->h = hue;
    this->s = saturation;
    this->v = value;
}
