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

    std::vector <KeyPoint<PORTAL_SIZE>> keyPoints;

    AnimationPtr animation;

public:
    explicit ShowScene(Installation *installation);

    void setup() override;

    void loop() override;

    void reset() override;

    void setupKeyPoints();
};

#endif //TIL_SHOWSCENE_H
