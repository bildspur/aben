#include <cmath>

//
// Created by Florian on 06.12.17.
//

#include <Arduino.h>
#include <model/light/Led.h>
#include "MathUtils.h"
#include "../model/Portal.h"

MathUtils::MathUtils() = default;

float MathUtils::map(float value, float minIn, float maxIn, float minOut, float maxOut) {
    return (value - minIn) * (maxOut - minOut) / (maxIn - minIn) + minOut;
}

float MathUtils::limit(float value, float min, float max) {
    return (value < max ? value : max) > min ? value : min;
}

float MathUtils::windowedSine(float x) {
    if (x < 0.0f || x > 1.0f)
        return 0.0f;

    return absSine(x);
}

bool MathUtils::isRandomCalled(float factor) {
    return (random(0, 1000) / 1000.0) > factor;
}

float MathUtils::mapFromLEDBrightness(float value, float minValue, float maxValue) {
    return MathUtils::map(value, LED_MIN_BRIGHTNESS, LED_MAX_BRIGHTNESS, minValue, maxValue);
}

unsigned long MathUtils::millisToSeconds(unsigned long millis) {
    return millis / 1000;
}

unsigned long MathUtils::secondsToMillis(unsigned long seconds) {
    return seconds * 1000;
}

float MathUtils::absSine(float x, float phaseShift) {
    // calculate sine
    return static_cast<float>(0.5 * (1 + sin(2 * PI * x + phaseShift)));
}

float MathUtils::lerp(float a, float b, float t) {
    return (1 - t) * a + t * b;
}

float MathUtils::randomFloat(float minValue, float maxValue, float precision) {
    return random(std::lround(minValue * precision), std::lround(maxValue * precision)) / precision;
}

template<typename T>
void MathUtils::randomShuffle(int iterations, T *array, int length) {
    for (int i = 0; i < iterations; i++) {
        // swap
        auto firstIndex = random(0, length);
        auto secondIndex = random(0, length);

        auto tmp = array[firstIndex];
        array[firstIndex] = array[secondIndex];
        array[secondIndex] = tmp;
    }
}

int *MathUtils::getRandomIndexes(int start, int end, int iterations) {
    int length = end - start;
    int *indexes = new int[length];
    for (int i = 0; i < length; i++) {
        indexes[i] = i + start;
    }
    randomShuffle<int>(iterations, indexes, length);
    return indexes;
}
