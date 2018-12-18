#include <utility>

//
// Created by Florian Bruggisser on 17.12.18.
//

#include "OSCDataBinding.h"

OSCDataBinding::OSCDataBinding(const char *address, OSCDataBinding::DataModelPtr model, bool publishOnReceive,
                               IOSCBindingConverter *converter)
        : OSCRule(address) {
    this->model = model;
    this->publishOnReceive = publishOnReceive;
    this->converter = converter;
}

void OSCDataBinding::receive(IOSCPublisher *publisher, OSCMessage &msg) {
    auto value = msg.getFloat(0);

    if (converter != nullptr)
        value = converter->convertInput(value);

    model->setOSCValue(value);

    if (publishOnReceive)
        publish(publisher);
}

void OSCDataBinding::publish(IOSCPublisher *publisher) {
    auto value = model->getOSCValue();

    if (converter != nullptr)
        value = converter->convertOutput(value);

    OSCMessage msg(getAddress());
    msg.add(value);
    publisher->sendMessage(msg);
}
