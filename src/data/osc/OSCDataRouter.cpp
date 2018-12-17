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
        rule->receive(publisher, msg);
    }
}

void OSCDataRouter::publishAll() {
    for (OSCRulePtr rule : rules) {
        rule->publish(publisher);
    }
}
