//
// Created by Florian Bruggisser on 17.12.18.
//

#ifndef ABEN_DATAMODEL_H
#define ABEN_DATAMODEL_H

#include <EEPROM.h>
#include <data/eeprom/IEEPROMDataModel.h>
#include <data/osc/IOSCDataModel.h>
#include "IDataModel.h"

template<typename T>
class DataModel : public IDataModel, public IEEPROMDataModel, public IOSCDataModel {

private:
    T value;
    T defaultValue;

public:
    explicit DataModel(T value);

    T get() const {
        return value;
    }

    void set(T value) {
        DataModel::value = value;
    }

    void reset() override;

    void saveToEEPROM(int address) override;

    void loadFromEEPROM(int address) override;

    int sizeInEEPROM() override;

    float getOSCValue() override;

    void setOSCValue(float value) override;
};

template<typename T>
DataModel<T>::DataModel(T value) {
    this->defaultValue = value;
    this->value = value;
}

template<typename T>
void DataModel<T>::reset() {
    this->value = defaultValue;
}

template<typename T>
void DataModel<T>::saveToEEPROM(int address) {
    EEPROM.put(address, value);
}

template<typename T>
void DataModel<T>::loadFromEEPROM(int address) {
    EEPROM.get(address, value);
}

template<typename T>
int DataModel<T>::sizeInEEPROM() {
    return sizeof(value);
}

template<typename T>
float DataModel<T>::getOSCValue() {
    return static_cast<float>(value);
}

template<typename T>
void DataModel<T>::setOSCValue(float value) {
    this->value = static_cast<T>(value);
}


#endif //ABEN_DATAMODEL_H
