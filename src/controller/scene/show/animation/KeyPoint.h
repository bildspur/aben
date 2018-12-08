//
// Created by Florian Bruggisser on 08.12.18.
//

#ifndef ABEN_SHOWKEYPOINT_H
#define ABEN_SHOWKEYPOINT_H

#include <model/color/RGBColor.h>
#include <model/color/HSVColor.h>
#include <model/color/ColorSpace.h>

template<int SIZE>
class KeyPoint {
private:
    float timeStamp;

    RGBColor *colors;

public:
    explicit KeyPoint(float timeStamp, RGBColor colors[SIZE]);

    explicit KeyPoint(float timeStamp, RGBColor color);

    explicit KeyPoint(float timeStamp, HSVColor colors[SIZE]);

    explicit KeyPoint(float timeStamp, HSVColor color);

    float getTimeStamp() const;

    const RGBColor *getColors() const;
};

template<int SIZE>
KeyPoint<SIZE>::KeyPoint(float timeStamp, RGBColor *colors) {
    this->timeStamp = timeStamp;
    this->colors = colors;
}

template<int SIZE>
float KeyPoint<SIZE>::getTimeStamp() const {
    return timeStamp;
}

template<int SIZE>
const RGBColor *KeyPoint<SIZE>::getColors() const {
    return colors;
}

template<int SIZE>
KeyPoint<SIZE>::KeyPoint(float timeStamp, RGBColor color) {
    this->timeStamp = timeStamp;
    this->colors = new RGBColor[SIZE];

    for (auto i = 0; i < SIZE; i++)
        this->colors[i] = color;
}

template<int SIZE>
KeyPoint<SIZE>::KeyPoint(float timeStamp, HSVColor *colors) {
    this->timeStamp = timeStamp;
    this->colors = new RGBColor[SIZE];

    for (auto i = 0; i < SIZE; i++)
        this->colors[i] = ColorSpace::hsvToRGB(colors[i]);
}

template<int SIZE>
KeyPoint<SIZE>::KeyPoint(float timeStamp, HSVColor color) : KeyPoint(timeStamp, ColorSpace::hsvToRGB(color)) {

}


#endif //ABEN_SHOWKEYPOINT_H
