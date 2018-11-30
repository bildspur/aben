//
// Created by Florian on 29.11.17.
//

#ifndef TIL_MOTIONSENSOR_H
#define TIL_MOTIONSENSOR_H


#include <cstdint>
#include <controller/TimeBasedController.h>
#include "../../BaseController.h"
#include "../../../util/Timer.h"

class MotionSensor {
private:

protected:
    explicit MotionSensor();

    bool motionDetected = false;

public:
    virtual void setup();

    virtual void measure();

    virtual bool isMotionDetected(bool clearFlag = false);
};

#endif //TIL_MOTIONSENSOR_H
