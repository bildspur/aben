//
// Created by Florian on 09.10.18.
//

#ifndef TIL_SERIALLIGHTRENDERER_H
#define TIL_SERIALLIGHTRENDERER_H


#include "LightRenderer.h"
#include "../../util/StopWatch.h"
#include "../../util/Timer.h"

class SerialLightRenderer : public LightRenderer {
private:
    StopWatch watch = StopWatch();

    Timer monitorTimer = Timer(33);
    Timer debugTimer = Timer(1000);

public:
    explicit SerialLightRenderer(Installation *installation);

    void setup() override;

    void loop() override;

    void render(PortalPtr portal) override;
};


#endif //TIL_SERIALLIGHTRENDERER_H
