//
// Created by Florian on 06.12.17.
//

#ifndef SILVA_FLOATUTIL_H
#define SILVA_FLOATUTIL_H

#include <Arduino.h>

class MathUtils {
protected:
    MathUtils();

public:
    static float map(float value, float minIn, float maxIn, float minOut, float maxOut);

    static float limit(float value, float min, float max);

    static float windowedSine(float x);

    static float absSine(float x, float phaseShift = PI * -0.5);

    static bool isRandomCalled(float factor);

    static float randomFloat(float minValue, float maxValue, float precision = 1000.0f);

    template<typename T>
    static void randomShuffle(int iterations, T array[], int length);

    static int *getRandomIndexes(int start, int end, int iterations);

    static int *getIndexes(int start, int end);

    static float mapFromLEDBrightness(float value, float minValue, float maxValue);

    static unsigned long secondsToMillis(unsigned long seconds);

    static unsigned long millisToSeconds(unsigned long millis);

    static float lerp(float x, float y, float mix);
};


#endif //SILVA_FLOATUTIL_H
