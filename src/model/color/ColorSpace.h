//
// Created by Florian Bruggisser on 21.11.18.
//

#ifndef ABEN_COLORSPACE_H
#define ABEN_COLORSPACE_H


#include "HSVColor.h"
#include "RGBColor.h"

class ColorSpace {
private:
    explicit ColorSpace();

public:
    static HSVColor rgbToHSV(RGBColor in);

    static RGBColor hsvToRGB(HSVColor in);
};


#endif //ABEN_COLORSPACE_H
