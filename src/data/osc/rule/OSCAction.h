#include <utility>

//
// Created by Florian Bruggisser on 17.12.18.
//

#ifndef ABEN_OSCACTION_H
#define ABEN_OSCACTION_H


#include <functional>
#include <WString.h>
#include "OSCRule.h"

class OSCAction : public OSCRule {
    // based on: https://stackoverflow.com/a/9186537/1138326

    std::function<void(IOSCPublisher *publisher)> function;

public:
    explicit OSCAction(const char *address, std::function<void(IOSCPublisher *publisher)> f);

    void receive(IOSCPublisher *publisher, OSCMessage &msg) override;

    void publish(IOSCPublisher *publisher) override;
};


#endif //ABEN_OSCACTION_H
