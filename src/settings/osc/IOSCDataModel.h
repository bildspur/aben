//
// Created by Florian Bruggisser on 17.12.18.
//

#ifndef ABEN_OSCDATAMODEL_H
#define ABEN_OSCDATAMODEL_H


class IOSCDataModel {
public:
    virtual float getOSCValue() = 0;

    virtual void setOSCValue(float value) = 0;
};


#endif //ABEN_OSCDATAMODEL_H
