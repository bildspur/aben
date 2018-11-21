//
// Created by Florian Bruggisser on 21.11.18.
//

#include <model/color/ColorSpace.h>
#include "RGBLed.h"

RGBLed::RGBLed(float easingSpeed) {
    r = Led(easingSpeed);
    g = Led(easingSpeed);
    b = Led(easingSpeed);
}

void RGBLed::update() {
    r.update();
    g.update();
    b.update();
}

void RGBLed::turnOn(bool easing) {
    setBrightness(LED_MAX_BRIGHTNESS, easing);
}

void RGBLed::turnOff(bool easing) {
    setBrightness(LED_MIN_BRIGHTNESS, easing);
}

void RGBLed::setBrightness(float value, bool easing) {
    setRed(value, easing);
    setGreen(value, easing);
    setBlue(value, easing);
}

float RGBLed::getBrightness() {
    return (r.getBrightness() + g.getBrightness() + b.getBrightness()) / 3.0f;
}

void RGBLed::setRed(float value, bool easing) {
    r.setBrightness(value, easing);
}

void RGBLed::setGreen(float value, bool easing) {
    g.setBrightness(value, easing);
}

void RGBLed::setBlue(float value, bool easing) {
    b.setBrightness(value, easing);
}

float RGBLed::getRed() {
    return r.getBrightness();
}

float RGBLed::getGreen() {
    return g.getBrightness();
}

float RGBLed::getBlue() {
    return b.getBrightness();
}

void RGBLed::setRGB(RGBColor color) {
    setRed(color.r);
    setGreen(color.g);
    setBlue(color.b);
}

RGBColor RGBLed::getRGB() {
    return {getRed(), getGreen(), getBlue()};
}

void RGBLed::setHSV(HSVColor color) {
    setRGB(ColorSpace::hsvToRGB(color));
}

HSVColor RGBLed::getHSV() {
    return ColorSpace::rgbToHSV(getRGB());
}
