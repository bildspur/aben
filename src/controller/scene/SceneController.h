//
// Created by Florian on 04.12.17.
//

#ifndef SILVA_SCENECONTROLLER_H
#define SILVA_SCENECONTROLLER_H

#include "BaseScene.h"

class SceneController : public TimeBasedController {
private:
    Installation *installation;

    BaseScene *activeScene;

    bool running = true;


public:
    explicit SceneController(Installation *installation, BaseScene *defaultScene);

    void setup() override;

    void timedLoop() override;

    virtual BaseScene *getActiveScene() const;

    virtual void setActiveScene(BaseScene *activeScene);

    virtual bool isRunning() const;

    virtual void setRunning(bool running);

    virtual void changeScene(BaseScene *scene);
};

#endif //SILVA_SCENECONTROLLER_H
