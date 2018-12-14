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

    portalScene->setup();
    showScene->setup();
}

void AbenSceneController::timedLoop() {
    SceneController::timedLoop();
    selectRelevantScene();
}

void AbenSceneController::selectRelevantScene() {
    bool allActivated = areAllPortalsActivated();

    // switch to show scene
    if (allActivated && getActiveScene() != showScene
        && installation->getSettings().isInteractionOn()) {
        changeScene(showScene);

        // turn all doors off
        for (uint8_t i = 0; i < installation->getSize(); i++) {
            installation->getPortal(i)->setActivated(false);
        }

        installation->getSettings().incActivatedShowStats();

        Serial.println("switched to show scene!");
    }

    if (getActiveScene() == showScene && showScene->isFinished()) {
        changeScene(portalScene);
        Serial.println("switched to portal scene!");
    }
}

bool AbenSceneController::areAllPortalsActivated() {
    auto activatedCounter = 0;
    for (uint8_t i = 0; i < installation->getSize(); i++) {
        if (installation->getPortal(i)->isActivated())
            activatedCounter++;
    }
    return activatedCounter >= installation->getSettings().getMinPortalToActivate();
}
