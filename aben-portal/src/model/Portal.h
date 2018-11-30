//
// Created by Florian on 27.11.17.
//

#ifndef SILVA_LEAF_H
#define SILVA_LEAF_H

#include "../util/EasingValue.h"

class Portal {
private:
    unsigned short id;

    bool activated;

    unsigned long activatedTimeStamp = 0;

public:
    explicit Portal(unsigned short id);

    void update();

    unsigned short getId();

    bool isActivated() const;

    void setActivated(bool activated);
};


#endif //SILVA_LEAF_H
