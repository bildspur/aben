//
// Created by Florian Bruggisser on 22.11.18.
//

#ifndef ABEN_PIRARRAYSENSOR_H
#define ABEN_PIRARRAYSENSOR_H


#include "MotionSensor.h"

class PIRMotionSensor : public MotionSensor {
private:
    uint8_t pin;

    bool pinState = false;

public:
    explicit PIRMotionSensor(uint8_t pin, unsigned int updateFrequency = 250);

    void setup() override;

    void measure() override;
};


#endif //ABEN_PIRARRAYSENSOR_H
