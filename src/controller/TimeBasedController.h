//
// Created by Florian Bruggisser on 22.11.18.
//

#ifndef ABEN_TIMEBASEDCONTROLLER_H
#define ABEN_TIMEBASEDCONTROLLER_H


#include <util/Timer.h>
#include "BaseController.h"

class TimeBasedController : public BaseController {
private:
    Timer *loopTimer;

protected:
    explicit TimeBasedController(unsigned long waitTime = 0);

public:
    void setup() override;

    void loop() override;

    virtual void timedLoop();
};


#endif //ABEN_TIMEBASEDCONTROLLER_H
