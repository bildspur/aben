//
// Created by Florian Bruggisser on 21.11.18.
//

#include <util/MathUtils.h>
#include "RGBColor.h"

RGBColor::RGBColor() : RGBColor(0.0f, 0.0f, 0.0f) {

}

RGBColor::RGBColor(float red, float green, float blue) {
    this->r = red;
    this->g = green;
    this->b = blue;
}

RGBColor RGBColor::BLACK() {
    return {0.0f, 0.0f, 0.0f};
}

RGBColor RGBColor::WHITE() {
    return {1.0f, 1.0f, 1.0f};
}

RGBColor RGBColor::RED() {
    return {1.0f, 0.0f, 0.0f};
}

RGBColor RGBColor::lerp(RGBColor a, RGBColor b, float t) {
    return {
            MathUtils::lerp(a.r, b.r, t),
            MathUtils::lerp(a.g, b.g, t),
            MathUtils::lerp(a.b, b.b, t)
    };
}

RGBColor RGBColor::SATURATION(float saturation) {
    return {saturation, saturation, saturation};
}

String RGBColor::toString() {
    return String(r) + ", " + String(g) + ", " + String(b);
}

RGBColor RGBColor::shift(float dr, float dg, float db) {
    return {
            MathUtils::limit(getR() + dr, 0.0f, 1.0f),
            MathUtils::limit(getG() + dg, 0.0f, 1.0f),
            MathUtils::limit(getB() + db, 0.0f, 1.0f)
    };
}

float RGBColor::getR() const {
    return r;
}

float RGBColor::getG() const {
    return g;
}

float RGBColor::getB() const {
    return b;
}
