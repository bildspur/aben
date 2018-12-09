//
// Created by Florian Bruggisser on 25.10.18.
//

#ifndef TIL_SHOWSCENE_H
#define TIL_SHOWSCENE_H


#include <controller/scene/star/TimeStar.h>
#include <controller/scene/show/animation/Animation.h>
#include "../BaseScene.h"

#define PORTAL_SIZE 5

#define KEYPOINT_SIZE 45

class ShowScene : public BaseScene {
private:
    typedef Animation<PORTAL_SIZE> *AnimationPtr;

    float fadeInTime = 2.0f;
    float flashTime = 0.125f;

    KeyPoint<PORTAL_SIZE> keyPoints[KEYPOINT_SIZE]{
            // start
            KeyPoint<PORTAL_SIZE>(0.0f, RGBColor::BLACK()),
            KeyPoint<PORTAL_SIZE>(2.0f, RGBColor::BLACK()),

            // flash
            KeyPoint<PORTAL_SIZE>(flashTime, new RGBColor[PORTAL_SIZE]{RGBColor::SATURATION(0.5f),
                                                                       RGBColor::BLACK(),
                                                                       RGBColor::BLACK(),
                                                                       RGBColor::BLACK(),
                                                                       RGBColor::BLACK()}),
            KeyPoint<PORTAL_SIZE>(flashTime, RGBColor::BLACK()),
            KeyPoint<PORTAL_SIZE>(0.2, RGBColor::BLACK()),

            KeyPoint<PORTAL_SIZE>(flashTime, new RGBColor[PORTAL_SIZE]{RGBColor::BLACK(),
                                                                       RGBColor::BLACK(),
                                                                       RGBColor::SATURATION(0.75f),
                                                                       RGBColor::BLACK(),
                                                                       RGBColor::SATURATION(0.5f)}),
            KeyPoint<PORTAL_SIZE>(flashTime, RGBColor::BLACK()),
            KeyPoint<PORTAL_SIZE>(0.1, RGBColor::BLACK()),

            KeyPoint<PORTAL_SIZE>(flashTime, new RGBColor[PORTAL_SIZE]{RGBColor::BLACK(),
                                                                       RGBColor::SATURATION(0.75f),
                                                                       RGBColor::BLACK(),
                                                                       RGBColor::BLACK(),
                                                                       RGBColor::BLACK()}),
            KeyPoint<PORTAL_SIZE>(flashTime, RGBColor::BLACK()),
            KeyPoint<PORTAL_SIZE>(0.3, RGBColor::BLACK()),

            KeyPoint<PORTAL_SIZE>(flashTime, new RGBColor[PORTAL_SIZE]{RGBColor::SATURATION(0.75f),
                                                                       RGBColor::BLACK(),
                                                                       RGBColor::SATURATION(0.75f),
                                                                       RGBColor::SATURATION(0.5f),
                                                                       RGBColor::BLACK()}),
            KeyPoint<PORTAL_SIZE>(flashTime, RGBColor::BLACK()),
            KeyPoint<PORTAL_SIZE>(0.25, RGBColor::BLACK()),

            KeyPoint<PORTAL_SIZE>(flashTime, new RGBColor[PORTAL_SIZE]{RGBColor::BLACK(),
                                                                       RGBColor::SATURATION(0.5f),
                                                                       RGBColor::SATURATION(0.75f),
                                                                       RGBColor::BLACK(),
                                                                       RGBColor::SATURATION(0.5f)}),
            KeyPoint<PORTAL_SIZE>(flashTime, RGBColor::BLACK()),
            KeyPoint<PORTAL_SIZE>(0.05, RGBColor::BLACK()),

            KeyPoint<PORTAL_SIZE>(flashTime, new RGBColor[PORTAL_SIZE]{RGBColor::BLACK(),
                                                                       RGBColor::SATURATION(0.5f),
                                                                       RGBColor::SATURATION(0.75f),
                                                                       RGBColor::SATURATION(0.5f),
                                                                       RGBColor::SATURATION(0.5f)}),
            KeyPoint<PORTAL_SIZE>(flashTime, RGBColor::BLACK()),
            KeyPoint<PORTAL_SIZE>(0.2, RGBColor::BLACK()),

            KeyPoint<PORTAL_SIZE>(flashTime, new RGBColor[PORTAL_SIZE]{RGBColor::SATURATION(0.75f),
                                                                       RGBColor::BLACK(),
                                                                       RGBColor::BLACK(),
                                                                       RGBColor::BLACK(),
                                                                       RGBColor::BLACK()}),
            KeyPoint<PORTAL_SIZE>(flashTime, RGBColor::BLACK()),
            KeyPoint<PORTAL_SIZE>(0.25, RGBColor::BLACK()),

            // noise
            // first portal
            KeyPoint<PORTAL_SIZE>(fadeInTime, new RGBColor[PORTAL_SIZE]{RGBColor::SATURATION(0.5f),
                                                                        RGBColor::BLACK(),
                                                                        RGBColor::BLACK(),
                                                                        RGBColor::BLACK(),
                                                                        RGBColor::BLACK()}),
            KeyPoint<PORTAL_SIZE>(fadeInTime, RGBColor::BLACK()),
            KeyPoint<PORTAL_SIZE>(fadeInTime, new RGBColor[PORTAL_SIZE]{RGBColor::SATURATION(0.5f),
                                                                        RGBColor::BLACK(),
                                                                        RGBColor::BLACK(),
                                                                        RGBColor::BLACK(),
                                                                        RGBColor::BLACK()}),
            KeyPoint<PORTAL_SIZE>(fadeInTime, RGBColor::BLACK()),

            // second portal
            KeyPoint<PORTAL_SIZE>(fadeInTime, new RGBColor[PORTAL_SIZE]{RGBColor::SATURATION(0.5f),
                                                                        RGBColor::SATURATION(0.5f),
                                                                        RGBColor::BLACK(),
                                                                        RGBColor::BLACK(),
                                                                        RGBColor::BLACK()}),
            KeyPoint<PORTAL_SIZE>(fadeInTime, RGBColor::BLACK()),
            KeyPoint<PORTAL_SIZE>(fadeInTime, new RGBColor[PORTAL_SIZE]{RGBColor::SATURATION(0.5f),
                                                                        RGBColor::SATURATION(0.5f),
                                                                        RGBColor::BLACK(),
                                                                        RGBColor::BLACK(),
                                                                        RGBColor::BLACK()}),
            KeyPoint<PORTAL_SIZE>(fadeInTime, RGBColor::BLACK()),

            // third portal
            KeyPoint<PORTAL_SIZE>(fadeInTime, new RGBColor[PORTAL_SIZE]{RGBColor::SATURATION(0.5f),
                                                                        RGBColor::SATURATION(0.5f),
                                                                        RGBColor::SATURATION(0.5f),
                                                                        RGBColor::BLACK(),
                                                                        RGBColor::BLACK()}),
            KeyPoint<PORTAL_SIZE>(fadeInTime, RGBColor::BLACK()),
            KeyPoint<PORTAL_SIZE>(fadeInTime, new RGBColor[PORTAL_SIZE]{RGBColor::SATURATION(0.5f),
                                                                        RGBColor::SATURATION(0.5f),
                                                                        RGBColor::SATURATION(0.5f),
                                                                        RGBColor::BLACK(),
                                                                        RGBColor::BLACK()}),
            KeyPoint<PORTAL_SIZE>(fadeInTime, RGBColor::BLACK()),

            // fourth portal
            KeyPoint<PORTAL_SIZE>(fadeInTime, new RGBColor[PORTAL_SIZE]{RGBColor::SATURATION(0.5f),
                                                                        RGBColor::SATURATION(0.5f),
                                                                        RGBColor::SATURATION(0.5f),
                                                                        RGBColor::SATURATION(0.5f),
                                                                        RGBColor::BLACK()}),
            KeyPoint<PORTAL_SIZE>(fadeInTime, RGBColor::BLACK()),
            KeyPoint<PORTAL_SIZE>(fadeInTime, new RGBColor[PORTAL_SIZE]{RGBColor::SATURATION(0.5f),
                                                                        RGBColor::SATURATION(0.5f),
                                                                        RGBColor::SATURATION(0.5f),
                                                                        RGBColor::SATURATION(0.5f),
                                                                        RGBColor::BLACK()}),
            KeyPoint<PORTAL_SIZE>(fadeInTime, RGBColor::BLACK()),

            // fifth portal
            KeyPoint<PORTAL_SIZE>(fadeInTime, new RGBColor[PORTAL_SIZE]{RGBColor::SATURATION(0.5f),
                                                                        RGBColor::SATURATION(0.5f),
                                                                        RGBColor::SATURATION(0.5f),
                                                                        RGBColor::SATURATION(0.5f),
                                                                        RGBColor::SATURATION(0.5f)}),
            KeyPoint<PORTAL_SIZE>(fadeInTime, RGBColor::BLACK()),
            KeyPoint<PORTAL_SIZE>(fadeInTime, new RGBColor[PORTAL_SIZE]{RGBColor::SATURATION(0.5f),
                                                                        RGBColor::SATURATION(0.5f),
                                                                        RGBColor::SATURATION(0.5f),
                                                                        RGBColor::SATURATION(0.5f),
                                                                        RGBColor::SATURATION(0.5f)}),
            KeyPoint<PORTAL_SIZE>(fadeInTime, RGBColor::BLACK()),


            // end
            KeyPoint<PORTAL_SIZE>(5.0f, RGBColor::BLACK()),
            KeyPoint<PORTAL_SIZE>(2.0f, RGBColor::BLACK()),
    };

    AnimationPtr animation;

public:
    explicit ShowScene(Installation *installation);

    void setup() override;

    void loop() override;

    void reset() override;
};


#endif //TIL_SHOWSCENE_H
