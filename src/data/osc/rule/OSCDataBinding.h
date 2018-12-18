//
// Created by Florian Bruggisser on 17.12.18.
//

#ifndef ABEN_OSCDATAMODEL_H
#define ABEN_OSCDATAMODEL_H


#include <data/osc/IOSCDataModel.h>
#include <WString.h>
#include <data/osc/rule/converter/IOSCBindingConverter.h>
#include "OSCRule.h"

class OSCDataBinding : public OSCRule {
private:
    typedef IOSCDataModel *DataModelPtr;

    bool publishOnReceive;

    IOSCBindingConverter *converter;

public:
    DataModelPtr model;

    explicit OSCDataBinding(const char *address, DataModelPtr model, bool publishOnReceive = false,
                            IOSCBindingConverter *converter = nullptr);

    void receive(IOSCPublisher *publisher, OSCMessage &msg) override;

    void publish(IOSCPublisher *publisher) override;
};


#endif //ABEN_OSCDATAMODEL_H
