//
// Created by Florian Bruggisser on 25.10.18.
//

#ifndef TIL_SHOWSCENE_H
#define TIL_SHOWSCENE_H


#include <controller/scene/star/TimeStar.h>
#include <controller/scene/show/animation/Animation.h>
#include "../BaseScene.h"

#define PORTAL_SIZE 5
#define ANIMATION_SPEED 1000

class ShowScene : public BaseScene {
private:
    typedef Animation<PORTAL_SIZE> *AnimationPtr;

    KeyPoint<PORTAL_SIZE> keyPoints[3]{
            KeyPoint<PORTAL_SIZE>(1.0f, RGBColor::BLACK()),
            KeyPoint<PORTAL_SIZE>(5.0f, RGBColor::WHITE()),
            KeyPoint<PORTAL_SIZE>(8.0f, RGBColor::BLACK()),
    };

    AnimationPtr animation;

public:
    explicit ShowScene(Installation *installation);

    void setup() override;

    void loop() override;

    void reset() override;
};


#endif //TIL_SHOWSCENE_H
