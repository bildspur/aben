//
// Created by Florian Bruggisser on 21.11.18.
//

#ifndef ABEN_RGBLED_H
#define ABEN_RGBLED_H


#include <model/color/RGBColor.h>
#include <model/color/HSVColor.h>
#include "Led.h"

class RGBLed {

private:
    Led r;
    Led g;
    Led b;

public:
    explicit RGBLed(float easingSpeed = EASING_SPEED);

    void update();

    void turnOn(bool easing = true);

    void turnOff(bool easing = true);

    void setBrightness(float value, bool easing = true);

    float getBrightness();

    void setRed(float value, bool easing = true);

    void setGreen(float value, bool easing = true);

    void setBlue(float value, bool easing = true);

    float getRed();

    float getGreen();

    float getBlue();

    void setRGBChannel(unsigned int channel, float value, bool easing = true);

    float getRGBChannel(unsigned int channel);

    float getBGRChannel(unsigned int channel);

    unsigned int getChannelCount();

    void setRGB(RGBColor color, bool easing = true);

    RGBColor getRGB();

    void setHSV(HSVColor color, bool easing = true);

    HSVColor getHSV();
};


#endif //ABEN_RGBLED_H
