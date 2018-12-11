//
// Created by Florian Bruggisser on 21.11.18.
//

#ifndef ABEN_RGBCOLOR_H
#define ABEN_RGBCOLOR_H

#include "Arduino.h"

class RGBColor {
public:
    float r; // a fraction between 0 and 1
    float g; // a fraction between 0 and 1
    float b; // a fraction between 0 and 1

    explicit RGBColor();

    RGBColor(float red, float green, float blue);

    String toString();

    RGBColor shift(float dr, float dg, float db);

    static RGBColor lerp(RGBColor a, RGBColor b, float t);

    static RGBColor BLACK();

    static RGBColor WHITE();

    static RGBColor SATURATION(float saturation);

    static RGBColor RED();

    float getR() const;

    float getG() const;

    float getB() const;
};

#endif //ABEN_RGBCOLOR_H
