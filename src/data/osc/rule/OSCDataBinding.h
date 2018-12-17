//
// Created by Florian Bruggisser on 17.12.18.
//

#ifndef ABEN_OSCDATAMODEL_H
#define ABEN_OSCDATAMODEL_H


#include <data/osc/IOSCDataModel.h>
#include <WString.h>
#include "OSCRule.h"

class OSCDataBinding : public OSCRule {
private:
    typedef IOSCDataModel *DataModelPtr;

    bool publishOnReceive;

public:
    DataModelPtr model;

    explicit OSCDataBinding(String address, DataModelPtr model, bool publishOnReceive = false);

    void receive(IOSCPublisher *publisher, OSCMessage &msg) override;

    void publish(IOSCPublisher *publisher) override;
};


#endif //ABEN_OSCDATAMODEL_H
