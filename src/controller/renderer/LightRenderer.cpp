//
// Created by Florian on 06.12.17.
//

#include <model/light/Led.h>
#include "LightRenderer.h"
#include "../../util/MathUtils.h"

LightRenderer::LightRenderer(Installation *installation) {
    this->installation = installation;
}

void LightRenderer::setup() {
    BaseController::setup();
}

void LightRenderer::loop() {
    BaseController::loop();

    for (auto i = 0; i < installation->getSize(); i++) {
        auto leaf = installation->getPortal(i);
        render(leaf);
    }
}

void LightRenderer::render(PortalPtr portal) {
    // send out data
}

float LightRenderer::mapToGlobalBrightnessRange(float value) {
    return MathUtils::map(value,
                          LED_MIN_BRIGHTNESS, LED_MAX_BRIGHTNESS,
                          installation->getSettings().getMinBrightness(),
                          installation->getSettings().getMaxBrightness());
}
