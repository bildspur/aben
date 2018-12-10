//
// Created by Florian Bruggisser on 25.10.18.
//

#include "ShowScene.h"
#include "../../../util/MathUtils.h"

ShowScene::ShowScene(Installation *installation) : BaseScene(
        "ShowScene", installation) {
}

void ShowScene::setup() {
    BaseScene::setup();

    setupKeyPoints();
    this->animation = new Animation<PORTAL_SIZE>(keyPoints, installation->getSettings().getShowSpeed());
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
    keyPoints.emplace_back(0.0f, RGBColor::BLACK());

    // start
    keyPoints.emplace_back(0.5f, 0, RGBColor::BLACK());
    keyPoints.emplace_back(0.5f, 1, RGBColor::BLACK());
    keyPoints.emplace_back(0.5f, 2, RGBColor::BLACK());
    keyPoints.emplace_back(0.5f, 3, RGBColor::BLACK());
    keyPoints.emplace_back(0.5f, 4, RGBColor::BLACK());

    // end
    keyPoints.emplace_back(0.5f, 0, RGBColor::WHITE());
    keyPoints.emplace_back(0.5f, 1, RGBColor::WHITE());
    keyPoints.emplace_back(0.5f, 2, RGBColor::WHITE());
    keyPoints.emplace_back(0.5f, 3, RGBColor::WHITE());
    keyPoints.emplace_back(0.5f, 4, RGBColor::WHITE());

    // flash
    for (int i = 0; i < 50; i++) {
        keyPoints.emplace_back(0.1f, i % 2 == 0 ? RGBColor::WHITE() : RGBColor::BLACK());
    }

    keyPoints.emplace_back(1.0f, RGBColor::BLACK());
    keyPoints.emplace_back(1.0f, RGBColor::BLACK());
}
