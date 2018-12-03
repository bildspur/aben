//
// Created by Florian on 28.11.17.
//

#ifndef SILVA_BASESCENE_H
#define SILVA_BASESCENE_H

#include "../BaseController.h"
#include "controller/app/Installation.h"

class BaseScene : public BaseController {
private:

protected:
    explicit BaseScene(const char *name, Installation *installation);

    Installation *installation;

    const char *name;

    bool finished = false;

public:
    void setup() override;

    void loop() override;

    const char *getName() const;

    bool isFinished() const;

    void setFinished(bool finished);

    virtual void reset();
};


#endif //SILVA_BASESCENE_H
