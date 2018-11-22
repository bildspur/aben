//
// Created by Florian Bruggisser on 22.11.18.
//

#ifndef ABEN_TIMEBASEDCONTROLLER_H
#define ABEN_TIMEBASEDCONTROLLER_H


#include <util/Timer.h>
#include "BaseController.h"

class TimeBasedController : public BaseController {
public:
    enum TimeType {
        MILLISECONDS,
        FRAMES_PER_SECOND
    };

private:
    Timer *loopTimer;

protected:
    explicit TimeBasedController(unsigned long time = 0, TimeType timeType = MILLISECONDS);

    ~TimeBasedController();

public:
    void setup() override;

    void loop() override;

    virtual void timedLoop();
};


#endif //ABEN_TIMEBASEDCONTROLLER_H
