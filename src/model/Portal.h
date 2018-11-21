//
// Created by Florian on 27.11.17.
//

#ifndef SILVA_LEAF_H
#define SILVA_LEAF_H

#include <model/light/RGBLed.h>
#include "../util/EasingValue.h"

class Portal {
private:
    unsigned short id;

    RGBLed led;

public:
    explicit Portal(unsigned short id);

    void update();

    unsigned short getId();
};


#endif //SILVA_LEAF_H
