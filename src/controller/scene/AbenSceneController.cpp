//
// Created by Florian on 04.12.17.
//

#include "AbenSceneController.h"
#include "SceneController.h"

AbenSceneController::AbenSceneController(Installation *installation, BaseScene *portalScene, BaseScene *showScene) :
        SceneController(installation, portalScene) {
    this->portalScene = portalScene;
    this->showScene = showScene;
}

void AbenSceneController::setup() {
    SceneController::setup();
}

void AbenSceneController::timedLoop() {
    SceneController::loop();

    selectRelevantScene();
}

void AbenSceneController::selectRelevantScene() {
    // switch to show scene
    if (areAllPortalsActivated() && getActiveScene() != showScene) {
        changeScene(showScene);
    }

    if (!areAllPortalsActivated() || showScene->isFinished()) {
        changeScene(portalScene);
    }
}

bool AbenSceneController::areAllPortalsActivated() {
    auto allActivated = true;
    for (int i = 0; i < installation->getSize(); i++) {
        if (!installation->getPortal(i)->isActivated())
            allActivated = false;
    }
    return allActivated;
}
