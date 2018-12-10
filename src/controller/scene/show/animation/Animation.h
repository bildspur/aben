//
// Created by Florian Bruggisser on 08.12.18.
//

#ifndef ABEN_ANIMATION_H
#define ABEN_ANIMATION_H

#include "Arduino.h"
#include "KeyPointSet.h"
#include <vector>


template<int SIZE>
class Animation {
private:
    typedef KeyPointSet<SIZE> *KeyPointSetPtr;

    std::vector<KeyPointSet<SIZE>> keyPoints;

    // time
    unsigned long startTime = 0;

    KeyPointSetPtr startKey;
    KeyPointSetPtr endKey;

    unsigned int speed;

    unsigned long summedKeyPointTime = 0;

    // values
    RGBColor values[SIZE];

    unsigned int keyIndex;

    void switchKeyIndex();

    bool running = false;

    void preInterpolateKeyPointSet();

    void printKeyPointSets();

public:
    explicit Animation(std::vector<KeyPointSet<SIZE>> &keyPoints, unsigned int speed = 1000);

    void start();

    void reset();

    void update();

    const RGBColor *getValues() const;

    unsigned long toMillis(float time);

    bool isRunning() const;

    unsigned int getSpeed() const;

    void setSpeed(unsigned int speed);
};

template<int SIZE>
void Animation<SIZE>::start() {
    reset();
    startTime = millis();
    running = true;

    Serial.println("show started!");
}

template<int SIZE>
void Animation<SIZE>::reset() {
    keyIndex = 0;
    summedKeyPointTime = 0;
    switchKeyIndex();
    running = false;

    Serial.println("show resetted!");
}

template<int SIZE>
void Animation<SIZE>::switchKeyIndex() {
    if (keyIndex + 1 >= keyPoints.size()) {
        running = false;
        Serial.println("show ended!");
        return;
    }

    // check start from black
    startKey = &keyPoints[keyIndex];
    endKey = &keyPoints[keyIndex + 1];

    // add to summed time
    summedKeyPointTime += toMillis(startKey->getTimeStamp());

    Serial.printf("Changed to start keypoint %d, Summed time: %d\n", keyIndex, summedKeyPointTime);

    keyIndex++;
}

template<int SIZE>
void Animation<SIZE>::update() {
    // calculate current normalized value of current time-span
    auto timeSinceStart = millis() - startTime;
    auto currentKeyTime = timeSinceStart - summedKeyPointTime;
    auto t = float(currentKeyTime) / toMillis(endKey->getTimeStamp());

    // switch if necessary (key time up)
    if (t > 1.0f) {
        switchKeyIndex();
        t = 0.0f;
    }

    // lerp different values
    auto startColors = startKey->getKeyPoints();
    auto endColors = endKey->getKeyPoints();

    for (auto i = 0; i < SIZE; i++) {
        // todo: implement more type interpolations
        values[i] = RGBColor::lerp(startColors[i].getColor(), endColors[i].getColor(), t);
    }
}

template<int SIZE>
const RGBColor *Animation<SIZE>::getValues() const {
    return values;
}

template<int SIZE>
unsigned long Animation<SIZE>::toMillis(float time) {
    return static_cast<unsigned long>(lround(time * speed));
}

template<int SIZE>
bool Animation<SIZE>::isRunning() const {
    return running;
}

template<int SIZE>
unsigned int Animation<SIZE>::getSpeed() const {
    return speed;
}

template<int SIZE>
void Animation<SIZE>::setSpeed(unsigned int speed) {
    Animation::speed = speed;
}

template<int SIZE>
Animation<SIZE>::Animation(std::vector<KeyPointSet<SIZE>> &keyPoints, unsigned int speed) {
    this->keyPoints = keyPoints;
    this->speed = speed;

    Serial.println("Pre PreInterpolation:");
    printKeyPointSets();

    //preInterpolateKeyPointSet();

    /*
    Serial.println("---");
    Serial.println("After PreInterpolation:");
    printKeyPointSets();
     */
}

template<int SIZE>
void Animation<SIZE>::preInterpolateKeyPointSet() {
    for (int i = 0; i < keyPoints.size(); i++) {
        KeyPointSet<SIZE> keyPointSet = keyPoints[i];

        for (int kpi = 0; kpi < SIZE; kpi++) {
            auto keyPoint = keyPointSet.getKeyPoint(kpi);

            // guard out if not relevant
            if (keyPoint->getType() != KeyPointType::CONTINUE)
                continue;

            // get last key point
            auto startKeyPoint = ((KeyPointSet<SIZE>) keyPoints[i - 1]).getKeyPoint(kpi);

            // find end keypoint
            KeyPoint *endKeyPoint = nullptr;
            float totalTweenTime = 0.0f;

            for (int si = i + 1; si < keyPoints.size(); si++) {
                auto nkeySet = ((KeyPointSet<SIZE>) keyPoints[i]);
                auto nkey = nkeySet.getKeyPoint(kpi);

                totalTweenTime += nkeySet.getTimeStamp();

                // check if finished
                if (nkey->getType() != CONTINUE) {
                    // found end key
                    endKeyPoint = nkey;
                    break;
                }
            }

            // calculate time and update all in betweens
            float currentTime = 0.0f;
            for (int si = i; si < keyPoints.size(); si++) {
                auto nkeySet = ((KeyPointSet<SIZE>) keyPoints[i]);
                auto nkey = nkeySet.getKeyPoint(kpi);

                // check if finished
                if (nkey->getType() != CONTINUE) {
                    break;
                }

                // calculate and set normalized time
                auto nt = currentTime / totalTweenTime;
                nkey->setColor(RGBColor::lerp(startKeyPoint->getColor(), endKeyPoint->getColor(), nt));
            }
        }
    }
}

template<int SIZE>
void Animation<SIZE>::printKeyPointSets() {
    for (int i = 0; i < keyPoints.size(); i++) {
        KeyPointSet<SIZE> keyPointSet = keyPoints[i];

        Serial.printf("KPS %d (%LU ms): ", i, toMillis(keyPointSet.getTimeStamp()));
        for (int j = 0; j < SIZE; j++) {
            auto keyPoint = keyPointSet.getKeyPoint(j);
            Serial.printf("KP(%d, [%s], %s) ", j, keyPoint->getColor().toString().c_str(),
                          keyPoint->getType() == LINEAR ? "LIN" : "CONT");
        }
        Serial.println();
    }
}

#endif //ABEN_ANIMATION_H
