//
// Created by Florian Bruggisser on 10.12.18.
//

#ifndef ABEN_KEYPOINT_H
#define ABEN_KEYPOINT_H


#include <model/color/RGBColor.h>
#include "KeyPointType.h"

class KeyPoint {
public:
    explicit KeyPoint();

    explicit KeyPoint(RGBColor color, KeyPointType type = LINEAR);

    RGBColor getColor() const;

    KeyPointType getType() const;

    void setColor(RGBColor color);

    void setType(KeyPointType type);

private:
    RGBColor color;

    KeyPointType type;
};


#endif //ABEN_KEYPOINT_H
