//
// Created by Florian Bruggisser on 17.12.18.
//

#ifndef ABEN_IEEPROMDATAMODEL_H
#define ABEN_IEEPROMDATAMODEL_H


class IEEPROMDataModel {
public:
    virtual void saveToEEPROM(int address) = 0;

    virtual void loadFromEEPROM(int address) = 0;

    virtual int sizeInEEPROM() = 0;

    virtual void reset() = 0;
};


#endif //ABEN_IEEPROMDATAMODEL_H
