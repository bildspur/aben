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
    for (OSCRulePtr rule : rules) {
        if (msg.fullMatch(rule->getAddress())) {
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

void OSCDataRouter::publish(String address) {
    publish(address.c_str());
}
