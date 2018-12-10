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
    auto nightBlue = HSVColor(240.0f, 1.0f, 0.25f);
    auto sunriseOrange = HSVColor(48.0f, 0.93f, 0.65f);
    auto sunYellow = HSVColor(56.0f, 0.57f, 0.80f);
    auto rainBlue = HSVColor(212.0f, 0.83f, 1.0f);
    auto rainSkyBlue = HSVColor(240.0f, 0.85f, 0.77f);
    auto sunsetRed = HSVColor(14.0f, 0.96f, 0.80f);

    // define vars
    auto rainTime = 60;
    auto rainFlashTime = 0.1f;
    auto rainProbabilityLow = 0.99f;
    auto rainProbabilityHigh = 0.7f;

    // define show
    keyPoints.clear();
    keyPoints.emplace_back(0.0f, black);

    // night scene
    keyPoints.emplace_back(1.0f, ColorSpace::hsvToRGB(nightBlue));
    addShiftedTween(5.0f, ColorSpace::hsvToRGB(nightBlue.shift(0.0f, 0.0f, 0.2f)));
    addShiftedTween(3.0f, ColorSpace::hsvToRGB(nightBlue));
    addShiftedTween(4.0f, ColorSpace::hsvToRGB(nightBlue.shift(0.0f, 0.0f, 0.4f)));

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
    keyPoints.emplace_back(6.0f, ColorSpace::hsvToRGB(rainSkyBlue.shift(0.0f, 0.0f, -0.2f)));
    keyPoints.emplace_back(3.0f, ColorSpace::hsvToRGB(rainSkyBlue));
    for (int i = 0; i < rainTime; i++) {
        auto mappedProbability = MathUtils::map(i, 0, rainTime, rainProbabilityLow, rainProbabilityHigh);
        auto keyPointSet = KeyPointSet<PORTAL_SIZE>(rainFlashTime,
                                                    new HSVColor[PORTAL_SIZE]{
                                                            MathUtils::isRandomCalled(mappedProbability) ? rainBlue
                                                                                                         : rainSkyBlue,
                                                            MathUtils::isRandomCalled(mappedProbability) ? rainBlue
                                                                                                         : rainSkyBlue,
                                                            MathUtils::isRandomCalled(mappedProbability) ? rainBlue
                                                                                                         : rainSkyBlue,
                                                            MathUtils::isRandomCalled(mappedProbability) ? rainBlue
                                                                                                         : rainSkyBlue,
                                                            MathUtils::isRandomCalled(mappedProbability) ? rainBlue
                                                                                                         : rainSkyBlue
                                                    }

        );

        // set chance of rain
        for (int r = 0; r < PORTAL_SIZE; r++) {
            if (MathUtils::isRandomCalled(mappedProbability)) {
                //keyPointSet.getKeyPoint(i)->setColor(ColorSpace::hsvToRGB(rainBlue));
            }
        }

        keyPoints.push_back(keyPointSet);
    }

    // end rain
    keyPoints.emplace_back(2.0f, ColorSpace::hsvToRGB(rainSkyBlue));
    for (int i = 0; i < rainTime; i++) {
        auto mappedProbability = MathUtils::map(i, 0, rainTime, rainProbabilityHigh, rainProbabilityLow);
        auto keyPointSet = KeyPointSet<PORTAL_SIZE>(rainFlashTime,
                                                    new HSVColor[PORTAL_SIZE]{
                                                            MathUtils::isRandomCalled(mappedProbability) ? rainBlue
                                                                                                         : rainSkyBlue,
                                                            MathUtils::isRandomCalled(mappedProbability) ? rainBlue
                                                                                                         : rainSkyBlue,
                                                            MathUtils::isRandomCalled(mappedProbability) ? rainBlue
                                                                                                         : rainSkyBlue,
                                                            MathUtils::isRandomCalled(mappedProbability) ? rainBlue
                                                                                                         : rainSkyBlue,
                                                            MathUtils::isRandomCalled(mappedProbability) ? rainBlue
                                                                                                         : rainSkyBlue
                                                    }

        );

        // set chance of rain
        for (int r = 0; r < PORTAL_SIZE; r++) {
            if (MathUtils::isRandomCalled(mappedProbability)) {
                //keyPointSet.getKeyPoint(i)->setColor(ColorSpace::hsvToRGB(rainBlue));
            }
        }

        keyPoints.push_back(keyPointSet);
    }
    keyPoints.emplace_back(3.0f, ColorSpace::hsvToRGB(rainSkyBlue.shift(0.0f, 0.0f, 0.2f)));

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
