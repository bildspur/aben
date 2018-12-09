//
// Created by Florian Bruggisser on 25.10.18.
//

#ifndef TIL_TIMESTARSCENE_H
#define TIL_TIMESTARSCENE_H


#include <controller/scene/star/TimeStar.h>
#include "../BaseScene.h"

class PortalScene : public BaseScene {
private:
    float getPortalBrightness(PortalPtr portal, unsigned long timeStamp, float blinkTime);

    Timer rainbowTimer = Timer(4000);

public:
    explicit PortalScene(Installation *installation);

    void setup() override;

    void loop() override;

    void reset() override;
};


#endif //TIL_TIMESTARSCENE_H
