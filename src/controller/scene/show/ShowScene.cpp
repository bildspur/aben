//
// Created by Florian Bruggisser on 25.10.18.
//

#include "ShowScene.h"
#include "../../../util/MathUtils.h"

ShowScene::ShowScene(Installation *installation) : BaseScene(
        "ShowScene", installation) {
    this->animation = new Animation<PORTAL_SIZE>(keyPoints, KEYPOINT_SIZE, ANIMATION_SPEED);
}

void ShowScene::setup() {
    BaseScene::setup();
}

void ShowScene::loop() {
    BaseScene::loop();

    animation->update();
    auto values = animation->getValues();

    for (auto i = 0; i < installation->getSize(); i++) {
        auto portal = installation->getPortal(i);

        // update color
        // todo: limit brightness of show!
        portal->getLed()->setRGB(values[i]);
    }
}

void ShowScene::reset() {
    BaseScene::reset();

    animation->reset();
    animation->start();
}
