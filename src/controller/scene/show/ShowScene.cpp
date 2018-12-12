#include <cmath>

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

    // show colors
    auto nightBlue = HSVColor(240.0f, 1.0f, 0.30f);
    auto nightBlueBright = nightBlue.shift(0.0f, 0.0f, 0.3f);

    auto sunriseOrange = HSVColor(48.0f, 0.93f, 0.65f);
    auto sunYellow = HSVColor(56.0f, 0.57f, 0.80f);
    auto rainBlue = HSVColor(212.0f, 0.83f, 1.0f);
    auto rainSkyBlue = HSVColor(240.0f, 0.85f, 0.77f);
    auto sunsetRed = HSVColor(14.0f, 0.96f, 0.80f);

    // define vars
    auto rainFlashTime = 0.1f;
    auto rainProbabilityLow = 0.99f;
    auto rainProbabilityHigh = 0.7f;

    // define show
    keyPoints.clear();
    keyPoints.emplace_back(0.0f, black);

    // night scene
    addShiftTween(8.0f,
                  ColorSpace::hsvToRGB(nightBlue),
                  ColorSpace::hsvToRGB(nightBlueBright), 0.8f, false);
    keyPoints.emplace_back(2.0f, nightBlueBright);

    // sunrise
    addShiftedTween(3.0f, ColorSpace::hsvToRGB(sunriseOrange.shift(0.0f, 0.0f, -0.2f)));
    keyPoints.emplace_back(3.0f, ColorSpace::hsvToRGB(sunriseOrange));

    // daylight
    keyPoints.emplace_back(5.0f, ColorSpace::hsvToRGB(sunYellow));
    addShiftedTween(3.0f, ColorSpace::hsvToRGB(sunYellow.shift(0.0f, 0.0f, -0.2f)));

    // clouds
    addShiftedTween(1.0f, ColorSpace::hsvToRGB(sunYellow.shift(0.0f, -0.3f, -0.2f)));
    keyPoints.emplace_back(2.0f, ColorSpace::hsvToRGB(sunYellow.shift(0.0f, 0.0f, -0.2f)));
    addShiftedTween(2.0f, ColorSpace::hsvToRGB(sunYellow.shift(0.0f, 0.0f, -0.2f)));
    keyPoints.emplace_back(2.0f, ColorSpace::hsvToRGB(sunYellow.shift(0.0f, 0.0f, -0.5f)));

    // start rain
    keyPoints.emplace_back(3.0f, ColorSpace::hsvToRGB(rainSkyBlue.shift(0.0f, 0.0f, -0.2f)));
    keyPoints.emplace_back(3.0f, ColorSpace::hsvToRGB(rainSkyBlue));
    addRandomFlashTween(10.0, rainFlashTime, rainProbabilityLow, rainProbabilityHigh,
                        ColorSpace::hsvToRGB(rainSkyBlue), ColorSpace::hsvToRGB((rainBlue)));

    // end rain
    keyPoints.emplace_back(rainFlashTime, ColorSpace::hsvToRGB(rainSkyBlue));
    addRandomFlashTween(10.0, rainFlashTime, rainProbabilityHigh, rainProbabilityLow,
                        ColorSpace::hsvToRGB(rainSkyBlue), ColorSpace::hsvToRGB((rainBlue)));
    keyPoints.emplace_back(2.0f, ColorSpace::hsvToRGB(rainSkyBlue.shift(0.0f, 0.0f, 0.2f)));

    // daylight
    addShiftedTween(5.0f, ColorSpace::hsvToRGB(sunYellow.shift(-0.10f, 0.0f, -0.2f)));

    // sunset
    addShiftedTween(5.0f, ColorSpace::hsvToRGB(sunsetRed.shift(0.0f, 0.0f, -0.2f)));
    keyPoints.emplace_back(3.0f, ColorSpace::hsvToRGB(sunsetRed));

    // night
    keyPoints.emplace_back(5.0f, ColorSpace::hsvToRGB(nightBlue.shift(0.0f, 0.0f, 0.8f)));
    addShiftedTween(5.0f, ColorSpace::hsvToRGB(nightBlue.shift(0.0f, 0.0f, 0.5f)));
    keyPoints.emplace_back(3.0f, ColorSpace::hsvToRGB(nightBlue));
    keyPoints.emplace_back(2.0f, ColorSpace::hsvToRGB(nightBlue));

    // end
    keyPoints.emplace_back(1.0f, black);
}

void ShowScene::addShiftedTween(float time, RGBColor color) {
    // end
    for (int i = 0; i < PORTAL_SIZE; i++) {
        keyPoints.emplace_back(time / PORTAL_SIZE, i, color);
    }
}

void ShowScene::addRandomFlashTween(float time, float flashTime, float startProbability, float endProbability,
                                    RGBColor baseColor, RGBColor flashColor) {
    auto discreteTime = time / flashTime;

    for (int i = 0; i < discreteTime; i++) {
        auto mappedProbability = MathUtils::map(i, 0, discreteTime, startProbability, endProbability);
        auto keyPointSet = KeyPointSet<PORTAL_SIZE>(flashTime, baseColor);

        // flash if probability matches
        for (int r = 0; r < PORTAL_SIZE; r++) {
            if (MathUtils::isRandomCalled(mappedProbability)) {
                keyPointSet.setKeyPoint(r, KeyPoint(flashColor));
            }
        }

        keyPoints.push_back(keyPointSet);
    }
}

void ShowScene::addShiftTween(float time, RGBColor startColor, RGBColor endColor,
                              float phaseShift, bool randomizePhase) {
    auto indexes = randomizePhase ? MathUtils::getRandomIndexes(0, PORTAL_SIZE, PORTAL_SIZE)
                                  : MathUtils::getIndexes(0, PORTAL_SIZE);

    float deltaTime = time - (2.0f * phaseShift);

    for (int i = 0; i < PORTAL_SIZE; i++) {
        keyPoints.emplace_back(phaseShift, indexes[i], startColor);
    }

    // wait for delta time
    keyPoints.emplace_back(_max(0.0f, deltaTime));

    for (int i = 0; i < PORTAL_SIZE; i++) {
        keyPoints.emplace_back(phaseShift, indexes[i], endColor);
    }

    delete indexes;
}
