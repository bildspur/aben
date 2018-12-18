#include <utility>

//
// Created by Florian Bruggisser on 17.12.18.
//

#include "OSCAction.h"

OSCAction::OSCAction(const char *address, std::function<void(IOSCPublisher *publisher, OSCMessage &msg)> f)
        : OSCRule(address), function(f) {

}

void OSCAction::receive(IOSCPublisher *publisher, OSCMessage &msg) {
    function(publisher, msg);
}

void OSCAction::publish(IOSCPublisher *publisher) {
    // do nothing
}
