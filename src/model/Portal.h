//
// Created by Florian on 27.11.17.
//

#ifndef SILVA_LEAF_H
#define SILVA_LEAF_H

#include <model/light/RGBLed.h>
#include <util/Timer.h>
#include "../util/EasingValue.h"

typedef RGBLed *RGBLedPtr;

class Portal {
private:
    unsigned short id;

    RGBLedPtr led;

    bool activated = false;

    unsigned long activatedTimeStamp = 0;

    long onlineTimeStamp = -100000;

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

    bool isOnline(unsigned long maxTimeSinceUpdate = 15000);

    void updateActivation(unsigned long activationTime);
};


#endif //SILVA_LEAF_H
