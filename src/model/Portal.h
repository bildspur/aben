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

    bool activated;

    unsigned long activatedTimeStamp = 0;

    unsigned long onlineTimeStamp = 0;

public:
    explicit Portal(unsigned short id);

    void update();

    unsigned short getId();

    void turnOn();

    void turnOff();

    RGBLedPtr getLed();

    bool isActivated() const;

    void setActivated(bool activated);

    void onlineStateReceived();
};


#endif //SILVA_LEAF_H
