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

    // setup stars
    this->starCount = installation->getSize();
    this->stars = new TimeStarPtr[starCount];

    // init stars
    for (auto i = 0; i < starCount; i++) {
        stars[i] = new TimeStar();
    }
}

void PortalScene::loop() {
    BaseScene::loop();

    auto timeStamp = millis();

    // rnd stars
    for (auto i = 0; i < starCount; i++) {
        auto star = stars[i];
        if (!star->isRunning(timeStamp)) {
            star->start(timeStamp, installation->getSettings().getTimeStarMaxDuration());
        }

        // update
        float brightness = star->getBrightness(timeStamp);
        float clampedBrightness = MathUtils::mapFromLEDBrightness(brightness,
                                                                  installation->getSettings().getTimeStarMinBrightness(),
                                                                  installation->getSettings().getTimeStarMaxBrightness());

        // check portal state
        auto portal = installation->getPortal(i);

        if (portal->isActivated()) {
            // todo: check activation time if needed

            // is activated
            portal->getLed()->setHSV(
                    HSVColor(installation->getSettings().getDefaultHue(),
                             installation->getSettings().getDefaultSaturation(),
                             clampedBrightness));
        } else {
            // not activated
            portal->getLed()->setHSV(
                    HSVColor(installation->getSettings().getDefaultHue(),
                             installation->getSettings().getDefaultSaturation(),
                             installation->getSettings().getTimeStarMaxBrightness()));
        }
    }
}

void PortalScene::resetStar(int id) {
    stars[id]->reset();
}
