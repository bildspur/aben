//
// Created by Florian Bruggisser on 21.11.18.
//

#ifndef ABEN_HSVCOLOR_H
#define ABEN_HSVCOLOR_H


class HSVColor {
public:
    float h; // angle in degrees
    float s; // a fraction between 0 and 1
    float v; // a fraction between 0 and 1

    explicit HSVColor();

    HSVColor(float hue, float saturation, float value);

    HSVColor shift(float dh, float ds, float dv);

    float getH() const;

    float getS() const;

    float getV() const;
};


#endif //ABEN_HSVCOLOR_H
