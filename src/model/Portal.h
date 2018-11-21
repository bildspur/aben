//
// Created by Florian on 27.11.17.
//

#ifndef SILVA_LEAF_H
#define SILVA_LEAF_H

#include <model/light/RGBLed.h>
#include "../util/EasingValue.h"

typedef RGBLed *RGBLedPtr;

class Portal {
private:
    unsigned short id;

    RGBLedPtr led;

public:
    explicit Portal(unsigned short id);

    void update();

    unsigned short getId();

    void turnOn();

    void turnOff();

    RGBLedPtr getLed();
};


#endif //SILVA_LEAF_H
