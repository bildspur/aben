//
// Created by Florian Bruggisser on 10.12.18.
//

#include "KeyPoint.h"

KeyPoint::KeyPoint(RGBColor color, KeyPointType type) {
    this->color = color;
    this->type = type;
}

RGBColor KeyPoint::getColor() const {
    return color;
}

KeyPointType KeyPoint::getType() const {
    return type;
}

KeyPoint::KeyPoint() : KeyPoint(RGBColor::BLACK(), LINEAR) {

}

void KeyPoint::setColor(RGBColor color) {
    KeyPoint::color = color;
}

void KeyPoint::setType(KeyPointType type) {
    KeyPoint::type = type;
}
