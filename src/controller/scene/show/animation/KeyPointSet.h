//
// Created by Florian Bruggisser on 08.12.18.
//

#ifndef ABEN_SHOWKEYPOINT_H
#define ABEN_SHOWKEYPOINT_H

#include <model/color/RGBColor.h>
#include <model/color/HSVColor.h>
#include <model/color/ColorSpace.h>
#include "KeyPoint.h"

template<int SIZE>
class KeyPointSet {
private:
    float timeStamp;

    KeyPoint *keyPoints;

public:
    explicit KeyPointSet(float timeStamp, RGBColor colors[SIZE]);

    explicit KeyPointSet(float timeStamp, RGBColor color);

    explicit KeyPointSet(float timeStamp, HSVColor colors[SIZE]);

    explicit KeyPointSet(float timeStamp, HSVColor color);

    float getTimeStamp() const;

    KeyPoint *getKeyPoints() const;
};

template<int SIZE>
KeyPointSet<SIZE>::KeyPointSet(float timeStamp, RGBColor *colors) {
    this->timeStamp = timeStamp;
    this->keyPoints = new KeyPoint[SIZE];

    for (auto i = 0; i < SIZE; i++)
        this->keyPoints[i] = KeyPoint(colors[i]);
}

template<int SIZE>
float KeyPointSet<SIZE>::getTimeStamp() const {
    return timeStamp;
}

template<int SIZE>
KeyPointSet<SIZE>::KeyPointSet(float timeStamp, RGBColor color) {
    this->timeStamp = timeStamp;
    this->keyPoints = new KeyPoint[SIZE];

    for (auto i = 0; i < SIZE; i++)
        this->keyPoints[i] = KeyPoint(color);
}

template<int SIZE>
KeyPointSet<SIZE>::KeyPointSet(float timeStamp, HSVColor *colors) {
    this->timeStamp = timeStamp;
    this->keyPoints = new RGBColor[SIZE];

    for (auto i = 0; i < SIZE; i++)
        this->keyPoints[i] = ColorSpace::hsvToRGB(colors[i]);
}

template<int SIZE>
KeyPointSet<SIZE>::KeyPointSet(float timeStamp, HSVColor color) : KeyPointSet(timeStamp, ColorSpace::hsvToRGB(color)) {

}

template<int SIZE>
KeyPoint *KeyPointSet<SIZE>::getKeyPoints() const {
    return keyPoints;
}


#endif //ABEN_SHOWKEYPOINT_H
