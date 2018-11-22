//
// Created by Florian on 06.12.17.
//

#ifndef SILVA_LIGHTRENDERER_H
#define SILVA_LIGHTRENDERER_H

#include <controller/TimeBasedController.h>
#include "../BaseController.h"
#include "../../model/Installation.h"

class LightRenderer : public TimeBasedController {
private:

protected:
    explicit LightRenderer(Installation *installation, unsigned long frameRate);

    Installation *installation;

public:
    void setup() override;

    void timedLoop() override;

    virtual void render(PortalPtr portal);

    float mapToGlobalBrightnessRange(float value);
};


#endif //SILVA_LIGHTRENDERER_H
