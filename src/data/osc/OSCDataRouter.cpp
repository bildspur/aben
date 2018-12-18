//
// Created by Florian Bruggisser on 17.12.18.
//

#include "OSCDataRouter.h"

OSCDataRouter::OSCDataRouter(IOSCPublisher *publisher) {
    this->publisher = publisher;
}

void OSCDataRouter::addRule(OSCDataRouter::OSCRulePtr rule) {
    rules.push_back(rule);
}

void OSCDataRouter::onReceive(OSCMessage &msg) {
    char *address = new char[50];
    msg.getAddress(address);

    for (OSCRulePtr rule : rules) {
        if (strcmp(address, rule->getAddress()) == 0) {
            rule->receive(publisher, msg);
        };
    }
}

void OSCDataRouter::publishAll() {
    for (OSCRulePtr rule : rules) {
        rule->publish(publisher);
    }
}

void OSCDataRouter::publish(const char *address) {
    for (OSCRulePtr rule : rules) {
        if (strcmp(address, rule->getAddress()) == 0) {
            rule->publish(publisher);
        };
    }
}

const std::vector<OSCDataRouter::OSCRulePtr> &OSCDataRouter::getRules() const {
    return rules;
}
