//
// Created by Florian on 30.11.17.
//

#include "Installation.h"
#include "../util/MathUtils.h"

Installation::Installation(uint16_t size, PortalPtr *portals) {
    this->size = size;
    this->portals = portals;
    this->settings = AppSettings();
}

uint16_t Installation::getSize() {
    return size;
}

PortalPtr *Installation::getPortals() {
    return portals;
}

PortalPtr Installation::getPortal(uint16_t index) {
    assert(index >= 0 && index < size);
    return portals[index];
}

PortalPtr Installation::getPortal(int index) {
    return getPortal(static_cast<uint16_t>(index));
}

void Installation::initPortals() {
    for (uint8_t i = 0; i < size; i++) {
        portals[i] = new Portal(i);
    }
}

void Installation::turnOn() {
    for (auto i = 0; i < size; i++) {
        portals[i]->turnOn();
    }
}

void Installation::turnOff() {
    for (auto i = 0; i < size; i++) {
        portals[i]->turnOff();
    }
}

void Installation::loadFromEEPROM() {
    if (!EEPROM.begin(EEPROM_SIZE)) {
        Serial.println("failed to initialise EEPROM");
        return;
    }

    // set start address
    int address = EEPROM_START_ADDRESS;
    EEPROM.get(address, settings);

    Serial.printf("Loaded Version: %d\n", settings.getVersion());

    // check version and set default if needed
    if (settings.getVersion() != ABEN_SETTINGS_VERSION) {
        Serial.println("applying default app settings!");
        loadDefaultSettings();
    }

    EEPROM.end();
}

void Installation::saveToEEPROM() {
    if (!EEPROM.begin(EEPROM_SIZE)) {
        Serial.println("failed to initialise EEPROM");
        return;
    }

    // set start address
    int address = EEPROM_START_ADDRESS;
    EEPROM.put(address, settings);

    EEPROM.commit();
    EEPROM.end();
}

AppSettings &Installation::getSettings() {
    return settings;
}

void Installation::loadDefaultSettings() {
    settings = AppSettings();
}
