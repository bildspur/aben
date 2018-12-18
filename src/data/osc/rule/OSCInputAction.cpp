#include <utility>

//
// Created by Florian Bruggisser on 17.12.18.
//

#include "OSCInputAction.h"

OSCInputAction::OSCInputAction(const char *address, OSCInFunction f)
        : OSCRule(address), function(f) {

}

void OSCInputAction::receive(IOSCPublisher *publisher, OSCMessage &msg) {
    function(publisher, msg);
}

void OSCInputAction::publish(IOSCPublisher *publisher) {
    // do nothing
}
