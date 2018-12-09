//
// Created by Florian Bruggisser on 25.10.18.
//

#include "ShowScene.h"
#include "../../../util/MathUtils.h"

ShowScene::ShowScene(Installation *installation) : BaseScene(
        "ShowScene", installation) {
    setupKeyPoints();
    this->animation = new Animation<PORTAL_SIZE>(keyPoints, installation->getSettings().getShowSpeed());
}

void ShowScene::setup() {
    BaseScene::setup();
}

void ShowScene::loop() {
    BaseScene::loop();

    animation->setSpeed(installation->getSettings().getShowSpeed());
    animation->update();
    auto values = animation->getValues();

    for (auto i = 0; i < installation->getSize(); i++) {
        auto portal = installation->getPortal(i);

        // update color
        portal->getLed()->setRGB(values[i], false);
    }

    if (!animation->isRunning())
        finished = true;
}

void ShowScene::reset() {
    BaseScene::reset();

    animation->reset();
    animation->start();
}

void ShowScene::setupKeyPoints() {
    keyPoints.clear();

    for (int i = 0; i < 20; i++) {
        auto on = MathUtils::isRandomCalled(0.8);

        if (i % 2 == 0)
            keyPoints.emplace_back(0.2f, RGBColor::WHITE());
        else
            keyPoints.emplace_back(0.2f, RGBColor::BLACK());
    }
}
