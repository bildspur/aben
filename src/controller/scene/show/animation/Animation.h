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

    KeyPoint<SIZE> *keyPoints;

    // time
    unsigned long startTime = 0;

    KeyPoint<SIZE> *startKey;
    KeyPoint<SIZE> *endKey;

    unsigned int speed;

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

}

template<int SIZE>
Animation<SIZE>::Animation(KeyPoint<SIZE> *keyPoints, unsigned int speed) {
    this->keyPoints = keyPoints;
    this->speed = speed;
}

#endif //ABEN_ANIMATION_H
