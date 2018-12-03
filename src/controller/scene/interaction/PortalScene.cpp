//
// Created by Florian Bruggisser on 25.10.18.
//

#include "PortalScene.h"
#include "../../../util/MathUtils.h"

PortalScene::PortalScene(Installation *installation) : BaseScene(
        "PortalScene", installation) {
}

void PortalScene::setup() {
    BaseScene::setup();
}

void PortalScene::loop() {
    BaseScene::loop();

    auto timeStamp = millis();

    for (auto i = 0; i < installation->getSize(); i++) {
        auto portal = installation->getPortal(i);

        auto brightness = getPortalBrightness(portal, timeStamp,
                                              installation->getSettings().getTimeStarMinDuration());
        float clampedBrightness = MathUtils::mapFromLEDBrightness(brightness,
                                                                  installation->getSettings().getTimeStarMinBrightness(),
                                                                  installation->getSettings().getTimeStarMaxBrightness());

        // update hsv color
        portal->getLed()->setHSV(
                HSVColor(installation->getSettings().getDefaultHue(),
                         installation->getSettings().getDefaultSaturation(),
                         clampedBrightness
                )
        );
    }
}

float PortalScene::getPortalBrightness(PortalPtr portal, unsigned long timeStamp, float blinkTime) {
    if (!portal->isActivated())
        return LED_MAX_BRIGHTNESS;

    // portal is activated
    auto nvalue = (timeStamp - portal->getActivatedTimeStamp()) / blinkTime;
    return MathUtils::absSine(nvalue, static_cast<float>(PI));
}
