//
// Created by Florian Bruggisser on 22.11.18.
//

#ifndef ABEN_PIRARRAYSENSOR_H
#define ABEN_PIRARRAYSENSOR_H


#include <NewPing.h>
#include "MotionSensor.h"

class HCSR04MotionSensor : public MotionSensor {
private:
    typedef NewPing *NewPingPtr;

    uint8_t triggerPin;
    uint8_t echoPin;

    float minThreshold;

    float maxDistance = 200;

    // temperature
    float theta = 22;

    float preciseSonicSpeed();

    NewPingPtr sensor;

public:
    explicit HCSR04MotionSensor(uint8_t triggerPin, uint8_t echoPin, float minThreshold = 30.0);

    void setup() override;

    void measure() override;

    float getMinThreshold() const;

    void setMinThreshold(float minThreshold);

    float getMaxDistance() const;

    void setMaxDistance(float maxDistance);

    float getTheta() const;

    void setTheta(float theta);
};


#endif //ABEN_PIRARRAYSENSOR_H
