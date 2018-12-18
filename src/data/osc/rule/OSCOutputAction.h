//
// Created by Florian Bruggisser on 18.12.18.
//

#ifndef ABEN_OSCOUTPUTACTION_H
#define ABEN_OSCOUTPUTACTION_H


#include <functional>
#include "OSCRule.h"

class OSCOutputAction : public OSCRule {
    // based on: https://stackoverflow.com/a/9186537/1138326
    typedef std::function<void(IOSCPublisher *publisher)> OSCOutFunction;

    OSCOutFunction function;

public:
    explicit OSCOutputAction(const char *address, OSCOutFunction f);

    void receive(IOSCPublisher *publisher, OSCMessage &msg) override;

    void publish(IOSCPublisher *publisher) override;
};


#endif //ABEN_OSCOUTPUTACTION_H
