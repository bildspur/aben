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

    rainbowTimer.setWaitTime(installation->getSettings()->getRainbowTime());
    rainbowTimer.reset();
}

void PortalScene::loop() {
    BaseScene::loop();

    auto timeStamp = millis();

    // update hue over 6 minutes
    if (installation->getSettings()->isRainbowMode() && rainbowTimer.elapsed()) {
        auto defaultHue = installation->getSettings()->getDefaultHue();
        installation->getSettings()->setDefaultHue(((int) defaultHue + 1) % 360);

        // keep it in the range
        if (defaultHue < installation->getSettings()->getRainbowStart() &&
            defaultHue > installation->getSettings()->getRainbowEnd()) {
            installation->getSettings()->setDefaultHue(installation->getSettings()->getRainbowStart());
        }
    }

    for (auto i = 0; i < installation->getSize(); i++) {
        auto portal = installation->getPortal(i);

        auto brightness = getPortalBrightness(portal, timeStamp,
                                              installation->getSettings()->getTimeStarMinDuration());
        float clampedBrightness = MathUtils::mapFromLEDBrightness(brightness,
                                                                  installation->getSettings()->getTimeStarMinBrightness(),
                                                                  installation->getSettings()->getTimeStarMaxBrightness());

        // update hsv color
        portal->getLed()->setHSV(
                HSVColor(installation->getSettings()->getDefaultHue(),
                         installation->getSettings()->getDefaultSaturation(),
                         clampedBrightness
                )
        );

        // add flash
        // todo: make blink time a setting
        if (portal->isActivated() && (millis() - portal->getActivatedTimeStamp()) < 250) {
            portal->getLed()->setHSV(
                    HSVColor(installation->getSettings()->getDefaultHue(),
                             0.0f,
                             LED_MAX_BRIGHTNESS
                    ), false
            );
        }
    }
}

float PortalScene::getPortalBrightness(PortalPtr portal, unsigned long timeStamp, float blinkTime) {
    if (!portal->isActivated() || !installation->getSettings()->isInteractionOn())
        return LED_MAX_BRIGHTNESS;

    // portal is activated
    auto nvalue = (timeStamp - portal->getActivatedTimeStamp()) / blinkTime;
    return MathUtils::absSine(nvalue, static_cast<float>(PI));
}

void PortalScene::reset() {
    BaseScene::reset();
}
