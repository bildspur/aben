//
// Created by Florian Bruggisser on 10.12.18.
//

#ifndef ABEN_KEYPOINT_H
#define ABEN_KEYPOINT_H


#include <model/color/RGBColor.h>

class KeyPoint {
    enum KeyPointType {
        LINEAR,
        FIX,
        CONTINUE
    };

private:
    RGBColor color;

    KeyPointType type;

public:
    explicit KeyPoint();

    explicit KeyPoint(RGBColor color, KeyPointType type = LINEAR);

    RGBColor getColor() const;

    KeyPointType getType() const;
};


#endif //ABEN_KEYPOINT_H
