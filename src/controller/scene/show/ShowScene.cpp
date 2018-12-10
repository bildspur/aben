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

    //setupKeyPoints();
    setupNatureShow();
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
    // define colors
    auto black = RGBColor::BLACK();
    auto dark = RGBColor::SATURATION(0.3f);
    auto bright = RGBColor::SATURATION(0.85f);
    auto white = RGBColor::SATURATION(1.0f);

    auto firstAccent = ColorSpace::hsvToRGB(HSVColor(200.0f, 1.0f, 1.0f));
    auto secondAccent = ColorSpace::hsvToRGB(HSVColor(200.0f, 1.0f, 1.0f));

    // define times


    keyPoints.clear();
    keyPoints.emplace_back(0.0f, black);
    keyPoints.emplace_back(2.0f, dark);

    // flash
    for (int i = 0; i < 20; i++) {
        keyPoints.emplace_back(0.1f, i % 2 == 0 ? bright : white);
    }

    keyPoints.emplace_back(1.0f, dark);
    keyPoints.emplace_back(1.0f, black);
}

void ShowScene::setupNatureShow() {
    // define default colors
    auto black = RGBColor::BLACK();
    auto dark = RGBColor::SATURATION(0.3f);
    auto bright = RGBColor::SATURATION(0.85f);
    auto white = RGBColor::SATURATION(1.0f);

    // define times

    // shwow colors
    auto nightBlue = ColorSpace::hsvToRGB(HSVColor(240.0f, 1.0f, 0.25f));

    // define show
    keyPoints.clear();
    keyPoints.emplace_back(0.0f, black);

    // night scene
    keyPoints.emplace_back(5.0f, nightBlue);
    addShiftedTween(5.0f, nightBlue.shift(0.0f, 0.0f, 0.1f));
    addShiftedTween(5.0f, nightBlue.shift(0.0f, 0.0f, 0.1f));

    // start sunrise

    keyPoints.emplace_back(1.0f, black);
    keyPoints.emplace_back(1.0f, black);
}

void ShowScene::addShiftedTween(float time, RGBColor color) {
    // end
    for (int i = 0; i < PORTAL_SIZE; i++) {
        keyPoints.emplace_back(time / PORTAL_SIZE, i, color);
    }
}
