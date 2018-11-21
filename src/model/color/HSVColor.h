//
// Created by Florian Bruggisser on 21.11.18.
//

#ifndef ABEN_HSVCOLOR_H
#define ABEN_HSVCOLOR_H


struct HSVColor {
    float h; // angle in degrees
    float s; // a fraction between 0 and 1
    float v; // a fraction between 0 and 1

    explicit HSVColor();

    HSVColor(float hue, float saturation, float value);
};


#endif //ABEN_HSVCOLOR_H
