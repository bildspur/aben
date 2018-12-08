//
// Created by Florian Bruggisser on 08.12.18.
//

#ifndef ABEN_SHOWKEYPOINT_H
#define ABEN_SHOWKEYPOINT_H

#include <model/color/RGBColor.h>

template<int SIZE>
class KeyPoint {
private:
    float timeStamp;

    RGBColor *colors;

public:
    explicit KeyPoint(float timeStamp, RGBColor colors[SIZE]);

    explicit KeyPoint(float timeStamp, RGBColor color);

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


#endif //ABEN_SHOWKEYPOINT_H
