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

    //setupNatureShow();
    setupShortShow();
    this->animation = new Animation<PORTAL_SIZE>(keyPoints, installation->getSettings()->getShowSpeed());

    // show info
    float showTimeMs = animation->getShowTime() * animation->getSpeed() / 1000.0f;
    Serial.printf("Animation Time (s): %s\n", String(showTimeMs, 2).c_str());
}

void ShowScene::loop() {
    BaseScene::loop();

    animation->setSpeed(installation->getSettings()->getShowSpeed());
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

void ShowScene::setupNatureShow() {
    // define default colors
    auto black = RGBColor::BLACK();

    // show colors
    auto startColor = HSVColor(140.0f, 0.0f, 1.0f);
    auto nightBlue = HSVColor(240.0f, 1.0f, 0.50f);
    auto nightBlueBright = nightBlue.shift(5.0f, 0.0f, 0.3f);

    auto sunriseOrange = HSVColor(48.0f, 0.93f, 0.65f);
    auto sunriseOrangeDark = sunriseOrange.shift(-10, 0, 0);

    auto sunYellow = HSVColor(56.0f, 0.57f, 0.80f);
    auto sunYellowBright = sunYellow.shift(6.0f, 0.0f, 0.0f);

    auto rainBlue = HSVColor(212.0f, 0.83f, 1.0f);

    auto rainSkyBlue = HSVColor(220.0f, 0.85f, 0.77f);
    auto rainSkyBlueGreen = rainSkyBlue.shift(-20.0f, 0.0f, 0.0f);

    auto sunsetRed = HSVColor(14.0f, 0.96f, 0.80f);
    auto sunsetRedDark = sunsetRed.shift(5.0f, 0.0f, -0.05f);

    // define vars
    auto rainFlashTime = 0.1f;
    auto rainProbabilityLow = 0.99f;
    auto rainProbabilityHigh = 0.7f;

    // define show
    keyPoints.clear();
    keyPoints.emplace_back(0.0f, startColor);

    // night scene
    keyPoints.emplace_back(1.0f);
    addShiftTween(1.0f,
                  ColorSpace::hsvToRGB(nightBlue),
                  ColorSpace::hsvToRGB(nightBlueBright), 0.4f, true);
    keyPoints.emplace_back(0.5f, nightBlueBright);

    // sunrise
    keyPoints.emplace_back(1.05f);
    addShiftTween(1.5f,
                  ColorSpace::hsvToRGB(sunriseOrangeDark),
                  ColorSpace::hsvToRGB(sunriseOrange), 0.4f, true);
    keyPoints.emplace_back(0.5f, ColorSpace::hsvToRGB(sunriseOrange));

    // daylight
    keyPoints.emplace_back(1.0f);
    addShiftTween(1.5f,
                  ColorSpace::hsvToRGB(sunYellow),
                  ColorSpace::hsvToRGB(sunYellowBright), 0.2f, true);
    keyPoints.emplace_back(0.5f, ColorSpace::hsvToRGB(sunYellowBright));

    // start rain
    keyPoints.emplace_back(1.0f);
    keyPoints.emplace_back(0.5f, ColorSpace::hsvToRGB(rainSkyBlueGreen));
    keyPoints.emplace_back(0.5f, ColorSpace::hsvToRGB(rainSkyBlue));
    addRandomFlashTween(5.0, rainFlashTime, rainProbabilityLow, rainProbabilityHigh,
                        ColorSpace::hsvToRGB(rainSkyBlue), ColorSpace::hsvToRGB((rainBlue)));

    // end rain
    keyPoints.emplace_back(rainFlashTime, ColorSpace::hsvToRGB(rainSkyBlue));
    addRandomFlashTween(5.0, rainFlashTime, rainProbabilityHigh, rainProbabilityLow,
                        ColorSpace::hsvToRGB(rainSkyBlue), ColorSpace::hsvToRGB((rainBlue)));
    keyPoints.emplace_back(0.5f, ColorSpace::hsvToRGB(rainSkyBlueGreen));

    // daylight
    keyPoints.emplace_back(1.0f);
    keyPoints.emplace_back(0.5f, ColorSpace::hsvToRGB(sunYellow));
    addShiftTween(2.0f,
                  ColorSpace::hsvToRGB(sunYellow),
                  ColorSpace::hsvToRGB(sunsetRedDark), 0.3f, true);

    // sunset
    keyPoints.emplace_back(1.5f, ColorSpace::hsvToRGB(sunsetRed));

    // night
    keyPoints.emplace_back(2.0f, ColorSpace::hsvToRGB(nightBlue));

    // end
    keyPoints.emplace_back(1.0f, black);
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

void ShowScene::setupShortShow() {
    // define default colors

    // show colors
    auto black = RGBColor::BLACK();
    auto startColor = HSVColor(140.0f, 0.0f, 1.0f);

    auto sunriseOrange = HSVColor(48.0f, 0.93f, 0.65f);
    auto sunriseOrangeDark = sunriseOrange.shift(-10, 0, 0);

    auto rainSkyBlue = HSVColor(14.0f, 0.96f, 0.80f);
    auto rainSkyBlueGreen = rainSkyBlue.shift(-20.0f, 0.0f, 0.2f);

    // define vars
    auto rainFlashTime = 0.1f;
    auto rainProbabilityLow = 0.99f;
    auto rainProbabilityHigh = 0.7f;

    // define show
    keyPoints.clear();
    keyPoints.emplace_back(0.0f, startColor);

    // night scene
    keyPoints.emplace_back(1.0f);
    addShiftTween(0.5f,
                  ColorSpace::hsvToRGB(sunriseOrange),
                  ColorSpace::hsvToRGB(sunriseOrangeDark), 0.2f, true);

    keyPoints.emplace_back(0.2f, ColorSpace::hsvToRGB(rainSkyBlue));
    addRandomFlashTween(2.0, rainFlashTime, rainProbabilityLow, rainProbabilityHigh,
                        ColorSpace::hsvToRGB(rainSkyBlue), ColorSpace::hsvToRGB((rainSkyBlueGreen)));

    // end rain
    keyPoints.emplace_back(rainFlashTime, ColorSpace::hsvToRGB(rainSkyBlue));
    addRandomFlashTween(2.0, rainFlashTime, rainProbabilityHigh, rainProbabilityLow,
                        ColorSpace::hsvToRGB(rainSkyBlue), ColorSpace::hsvToRGB((rainSkyBlueGreen)));

    keyPoints.emplace_back(0.5f, sunriseOrangeDark);
}
