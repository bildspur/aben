//
// Created by Florian Bruggisser on 25.10.18.
//

#include "ShowScene.h"
#include "../../../util/MathUtils.h"

ShowScene::ShowScene(Installation *installation) : BaseScene(
        "ShowScene", installation) {
    this->animation = new Animation<PORTAL_SIZE>(keyPoints, ANIMATION_SPEED);
}

void ShowScene::setup() {
    BaseScene::setup();
}

void ShowScene::loop() {
    BaseScene::loop();

    for (auto i = 0; i < installation->getSize(); i++) {
        auto portal = installation->getPortal(i);

        auto brightness = 0.5f;
        float clampedBrightness = MathUtils::mapFromLEDBrightness(brightness,
                                                                  installation->getSettings().getTimeStarMinBrightness(),
                                                                  installation->getSettings().getTimeStarMaxBrightness());

        // update hsv color
        portal->getLed()->setHSV(HSVColor(0.0f, 1.0f, clampedBrightness));
    }
}

void ShowScene::reset() {
    BaseScene::reset();
}
