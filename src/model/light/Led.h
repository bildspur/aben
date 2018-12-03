//
// Created by Florian Bruggisser on 21.11.18.
//

#ifndef ABEN_LED_H
#define ABEN_LED_H

#include <util/EasingValue.h>

#define LED_MIN_BRIGHTNESS 0.0f
#define LED_MAX_BRIGHTNESS 1.0f

#define EASING_SPEED 0.05

class Led {
private:
    EasingValue brightness;

public:
    explicit Led(float easingSpeed = EASING_SPEED);

    void update();

    void turnOn(bool easing = true);

    void turnOff(bool easing = true);

    void setBrightness(float value, bool easing = true);

    float getBrightness();
};


#endif //ABEN_LED_H
