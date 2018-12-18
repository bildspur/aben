//
// Created by Florian Bruggisser on 17.12.18.
//

#include <EEPROM.h>
#include "EEPROMStorage.h"

EEPROMStorage::EEPROMStorage(unsigned int eepromStartAddress, unsigned int eepromSize) {
    this->eepromSize = eepromSize;
    this->eepromStartAddress = eepromStartAddress;
}

void EEPROMStorage::save() {
    if (!EEPROM.begin(eepromSize)) {
        Serial.println("failed to initialise EEPROM");
        return;
    }

    auto address = eepromStartAddress;
    for (auto dataModel : dataModels) {
        dataModel->saveToEEPROM(address);
        address += dataModel->sizeInEEPROM();
    }

    EEPROM.end();
}

void EEPROMStorage::load() {
    if (!EEPROM.begin(eepromSize)) {
        Serial.println("failed to initialise EEPROM");
        return;
    }

    auto address = eepromStartAddress;
    for (auto dataModel : dataModels) {
        dataModel->loadFromEEPROM(address);
        address += dataModel->sizeInEEPROM();
    }

    EEPROM.end();
}

void EEPROMStorage::add(EEPROMStorage::DataModelPtr dataModel) {
    dataModels.push_back(dataModel);
}

void EEPROMStorage::loadDefault() {
    for (auto dataModel : dataModels) {
        dataModel->reset();
    }
}
