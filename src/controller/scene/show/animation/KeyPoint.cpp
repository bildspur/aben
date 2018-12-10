//
// Created by Florian Bruggisser on 10.12.18.
//

#include "KeyPoint.h"

KeyPoint::KeyPoint(RGBColor color, KeyPoint::KeyPointType type) {
    this->color = color;
    this->type = type;
}

RGBColor KeyPoint::getColor() const {
    return color;
}

KeyPoint::KeyPointType KeyPoint::getType() const {
    return type;
}

KeyPoint::KeyPoint() : KeyPoint(RGBColor::BLACK(), LINEAR) {

}
