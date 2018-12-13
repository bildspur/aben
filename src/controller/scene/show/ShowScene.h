//
// Created by Florian Bruggisser on 25.10.18.
//

#ifndef TIL_SHOWSCENE_H
#define TIL_SHOWSCENE_H


#include <controller/scene/star/TimeStar.h>
#include "../BaseScene.h"
#include <controller/scene/show/animation/Animation.h>

#define PORTAL_SIZE 5

class ShowScene : public BaseScene {
private:
    typedef Animation<PORTAL_SIZE> *AnimationPtr;

    std::vector<KeyPointSet<PORTAL_SIZE>> keyPoints;

    AnimationPtr animation;

    void setupNatureShow();

    // show methods
    void addRandomFlashTween(float time, float flashTime,
                             float startProbability, float endProbability,
                             RGBColor baseColor, RGBColor flashColor);

    void addShiftTween(float time, RGBColor startColor, RGBColor endColor,
                       float phaseShift = 0.0f, bool randomizePhase = false);

    void addShiftedTween(float time, RGBColor color);

public:
    explicit ShowScene(Installation *installation);

    void setup() override;

    void loop() override;

    void reset() override;
};

#endif //TIL_SHOWSCENE_H
