#include <utility>

//
// Created by Florian Bruggisser on 17.12.18.
//

#include "OSCDataBinding.h"

OSCDataBinding::OSCDataBinding(const char *address, OSCDataBinding::DataModelPtr model, bool publishOnReceive)
        : OSCRule(address) {
    this->model = model;
    this->publishOnReceive = publishOnReceive;
}

void OSCDataBinding::receive(IOSCPublisher *publisher, OSCMessage &msg) {
    model->setOSCValue(msg.getFloat(0));

    if (publishOnReceive)
        publish(publisher);
}

void OSCDataBinding::publish(IOSCPublisher *publisher) {
    OSCMessage msg(getAddress());
    msg.add(model->getOSCValue());
    publisher->sendMessage(msg);
}
