#include <utility>

//
// Created by Florian Bruggisser on 17.12.18.
//

#include "OSCAction.h"

OSCAction::OSCAction(String address, std::function<void(IOSCPublisher *publisher)> f)
        : OSCRule(std::move(address)), function(std::move(f)) {

}

void OSCAction::receive(IOSCPublisher *publisher, OSCMessage &msg) {
    function(publisher);
}

void OSCAction::publish(IOSCPublisher *publisher) {
    // do nothing
}
