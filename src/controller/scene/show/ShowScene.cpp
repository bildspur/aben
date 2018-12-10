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
    keyPoints.push_back(KeyPointSet<PORTAL_SIZE>(0.0f, RGBColor::BLACK()));

    /*
    for (int i = 0; i < 20; i++) {
        auto on = MathUtils::isRandomCalled(0.8);

        if (i % 2 == 0)
            keyPoints.emplace_back(0.2f, RGBColor::WHITE());
        else
            keyPoints.emplace_back(0.2f, RGBColor::BLACK());
    }
     */

    keyPoints.push_back(KeyPointSet<PORTAL_SIZE>(0.0f, RGBColor::BLACK()));

    // start
    keyPoints.push_back(KeyPointSet<PORTAL_SIZE>(0.5f, 0, RGBColor::BLACK()));
    keyPoints.push_back(KeyPointSet<PORTAL_SIZE>(0.5f, 1, RGBColor::BLACK()));
    keyPoints.push_back(KeyPointSet<PORTAL_SIZE>(0.5f, 2, RGBColor::BLACK()));
    keyPoints.push_back(KeyPointSet<PORTAL_SIZE>(0.5f, 3, RGBColor::BLACK()));

    // end
    keyPoints.push_back(KeyPointSet<PORTAL_SIZE>(0.5f, 0, RGBColor::WHITE()));
    keyPoints.push_back(KeyPointSet<PORTAL_SIZE>(0.5f, 1, RGBColor::WHITE()));
    keyPoints.push_back(KeyPointSet<PORTAL_SIZE>(0.5f, 2, RGBColor::WHITE()));
    keyPoints.push_back(KeyPointSet<PORTAL_SIZE>(0.5f, 3, RGBColor::WHITE()));

    keyPoints.push_back(KeyPointSet<PORTAL_SIZE>(1.0f, RGBColor::BLACK()));
    keyPoints.push_back(KeyPointSet<PORTAL_SIZE>(1.0f, RGBColor::BLACK()));
}
