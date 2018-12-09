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

    unsigned long toMillis(float time);
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
    summedKeyPointTime = 0;
    switchKeyIndex();
    running = false;
}

template<int SIZE>
void Animation<SIZE>::switchKeyIndex() {
    if (keyIndex + 1 >= keyPointSize) {
        running = false;
        return;
    }

    // check start from black
    startKey = &keyPoints[keyIndex];
    endKey = &keyPoints[keyIndex + 1];

    // add to summed time
    summedKeyPointTime += toMillis(startKey->getTimeStamp());

    keyIndex++;
}

template<int SIZE>
void Animation<SIZE>::update() {
    // calculate current normalized value of current time-span
    auto timeSinceStart = millis() - startTime;
    auto currentKeyTime = timeSinceStart - summedKeyPointTime;
    auto t = float(currentKeyTime) / toMillis(startKey->getTimeStamp());

    // switch if necessary (key time up)
    if (t > 1.0f) {
        switchKeyIndex();
        t = 0.0f;
    }

    // lerp different values
    auto startColors = startKey->getColors();
    auto endColors = endKey->getColors();

    for (auto i = 0; i < SIZE; i++) {
        values[i] = RGBColor::lerp(startColors[i], endColors[i], t);
    }
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

template<int SIZE>
unsigned long Animation<SIZE>::toMillis(float time) {
    return static_cast<unsigned long>(lround(time * speed));
}

#endif //ABEN_ANIMATION_H
