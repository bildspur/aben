#include <utility>

//
// Created by Florian Bruggisser on 17.12.18.
//

#ifndef ABEN_OSCINPUTACTION_H
#define ABEN_OSCINPUTACTION_H


#include <functional>
#include <WString.h>
#include "OSCRule.h"

class OSCInputAction : public OSCRule {
    // based on: https://stackoverflow.com/a/9186537/1138326
    typedef std::function<void(IOSCPublisher *publisher, OSCMessage &msg)> OSCInFunction;

    OSCInFunction function;

public:
    explicit OSCInputAction(const char *address, OSCInFunction f);

    void receive(IOSCPublisher *publisher, OSCMessage &msg) override;

    void publish(IOSCPublisher *publisher) override;
};


#endif //ABEN_OSCINPUTACTION_H
