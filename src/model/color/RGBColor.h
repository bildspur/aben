//
// Created by Florian Bruggisser on 21.11.18.
//

#ifndef ABEN_RGBCOLOR_H
#define ABEN_RGBCOLOR_H


struct RGBColor {
    float r; // a fraction between 0 and 1
    float g; // a fraction between 0 and 1
    float b; // a fraction between 0 and 1

    explicit RGBColor();

    RGBColor(float red, float green, float blue);

    static RGBColor lerp(RGBColor a, RGBColor b, float t);

    static RGBColor BLACK();

    static RGBColor WHITE();

    static RGBColor SATURATION(float saturation);

    static RGBColor RED();
};

#endif //ABEN_RGBCOLOR_H
