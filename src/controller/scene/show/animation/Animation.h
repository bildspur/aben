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

    // time
    unsigned long startTime = 0;

    KeyPointPtr startKey;
    KeyPointPtr endKey;

    unsigned int speed;

    unsigned long summedKeyPointTime = 0;

    // values
    float values[SIZE];

    unsigned int keyIndex;

    void switchKeyIndex();

public:
    explicit Animation(KeyPoint<SIZE> keyPoints[], unsigned int speed = 1000);

    void start();

    void reset();

    void update();
};

template<int SIZE>
void Animation<SIZE>::start() {
    reset();
    startTime = millis();;
}

template<int SIZE>
void Animation<SIZE>::reset() {
    keyIndex = 0;
    switchKeyIndex();
}

template<int SIZE>
void Animation<SIZE>::switchKeyIndex() {
    startKey = keyPoints[keyIndex];
    endKey = keyPoints[keyIndex + 1];

    keyIndex++;
}

template<int SIZE>
void Animation<SIZE>::update() {
    // calculate current normalized value

    // lerp different values
}

template<int SIZE>
Animation<SIZE>::Animation(KeyPoint<SIZE> *keyPoints, unsigned int speed) {
    this->keyPoints = keyPoints;
    this->speed = speed;

    // clear values
    for (auto i = 0; i < SIZE; i++)
        values[i] = 0;
}

#endif //ABEN_ANIMATION_H
