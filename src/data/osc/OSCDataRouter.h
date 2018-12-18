//
// Created by Florian Bruggisser on 17.12.18.
//

#ifndef ABEN_OSCDATAROUTER_H
#define ABEN_OSCDATAROUTER_H

#undef min
#undef max

#include <vector>
#include <data/osc/rule/OSCRule.h>
#include "IOSCDataModel.h"

class OSCDataRouter {
private:
    typedef OSCRule *OSCRulePtr;

    std::vector<OSCRulePtr> rules;

    IOSCPublisher *publisher;

public:
    explicit OSCDataRouter(IOSCPublisher *publisher);

    void addRule(OSCRulePtr rule);

    void onReceive(OSCMessage &msg);

    void publishAll();

    void publish(const char *address);

    const std::vector<OSCRulePtr> &getRules() const;
};


#endif //ABEN_OSCDATAROUTER_H
