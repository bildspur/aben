//
// Created by Florian Bruggisser on 18.12.18.
//

#include "OSCOutputAction.h"

OSCOutputAction::OSCOutputAction(const char *address, OSCOutputAction::OSCOutFunction f)
        : OSCRule(address), function(f) {

}

void OSCOutputAction::receive(IOSCPublisher *publisher, OSCMessage &msg) {
    // do nothing
}

void OSCOutputAction::publish(IOSCPublisher *publisher) {
    function(publisher);
}
