//
// Created by Florian on 04.12.17.
//

#ifndef SILVA_ABEN_CONTROLLER_H
#define SILVA_ABEN_CONTROLLER_H

#include "BaseScene.h"
#include "SceneController.h"

class AbenSceneController : public SceneController {
private:
    Installation *installation;

    BaseScene *portalScene;

    BaseScene *showScene;

    bool areAllPortalsActivated();

public:
    explicit AbenSceneController(Installation *installation, BaseScene *portalScene, BaseScene *showScene);

    void setup() override;

    void timedLoop() override;

    void selectRelevantScene();
};

#endif //SILVA_ABEN_CONTROLLER_H
