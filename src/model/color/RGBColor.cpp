//
// Created by Florian Bruggisser on 21.11.18.
//

#include "RGBColor.h"

RGBColor::RGBColor() : RGBColor(0.0f, 0.0f, 0.0f) {

}

RGBColor::RGBColor(float red, float green, float blue) {
    this->r = red;
    this->g = green;
    this->b = blue;
}
