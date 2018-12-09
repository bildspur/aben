//
// Created by Florian Bruggisser on 08.12.18.
//

#ifndef ABEN_ANIMATION_H
#define ABEN_ANIMATION_H


#include "Arduino.h"
#include "KeyPoint.h"

template<int SIZE>
class Animation {
private:
    typedef KeyPoint<SIZE> *KeyPointPtr;

    KeyPoint<SIZE> *keyPoints;

    unsigned int keyPointSize = 0;

    // time
    unsigned long startTime = 0;

    KeyPointPtr startKey;
    KeyPointPtr endKey;

    unsigned int speed;

    unsigned long summedKeyPointTime = 0;

    // values
    RGBColor values[SIZE];

    unsigned int keyIndex;

    void switchKeyIndex();

    bool running = false;

public:
    explicit Animation(KeyPoint<SIZE> keyPoints[], unsigned int keyPointSize, unsigned int speed = 1000);

    void start();

    void reset();

    void update();

    const RGBColor *getValues() const;
};

template<int SIZE>
void Animation<SIZE>::start() {
    reset();
    startTime = millis();
    running = true;
}

template<int SIZE>
void Animation<SIZE>::reset() {
    keyIndex = 0;
    switchKeyIndex();
    running = false;
}

template<int SIZE>
void Animation<SIZE>::switchKeyIndex() {
    //if(keyIndex > keyPoints)

    startKey = &keyPoints[keyIndex];
    endKey = &keyPoints[keyIndex + 1];

    keyIndex++;
}

template<int SIZE>
void Animation<SIZE>::update() {
    // calculate current normalized value

    // lerp different values
}

template<int SIZE>
const RGBColor *Animation<SIZE>::getValues() const {
    return values;
}

template<int SIZE>
Animation<SIZE>::Animation(KeyPoint<SIZE> *keyPoints, unsigned int keyPointSize, unsigned int speed) {
    this->keyPoints = keyPoints;
    this->speed = speed;
    this->keyPointSize = keyPointSize;
}

#endif //ABEN_ANIMATION_H
