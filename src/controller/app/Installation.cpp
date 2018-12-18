//
// Created by Florian on 30.11.17.
//

#include "Installation.h"
#include "util/MathUtils.h"

Installation::Installation(uint16_t size, PortalPtr *portals, OSCDataRouter *oscDataRouter) :
        TimeBasedController(APP_FRAME_RATE, FRAMES_PER_SECOND) {

    this->size = size;
    this->portals = portals;
    this->oscDataRouter = oscDataRouter;
    this->settingsStorage = new EEPROMStorage(EEPROM_START_ADDRESS, EEPROM_SIZE);

    this->settings = new AppSettings(oscDataRouter, settingsStorage);
    this->autoSaveTimer = new Timer(settings->getAutoSaveTime());
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
        portals[i]->getLed()->setHSV(
                HSVColor(settings->getDefaultHue(),
                         settings->getDefaultSaturation(),
                         1.0f));
    }
}

void Installation::turnOff() {
    for (auto i = 0; i < size; i++) {
        portals[i]->getLed()->setHSV(
                HSVColor(settings->getDefaultHue(),
                         settings->getDefaultSaturation(),
                         0.0f));
    }
}

void Installation::loadFromEEPROM() {
    settingsStorage->load();
    Serial.printf("Loaded Version: %d\n", settings->getVersion());

    // check version and set default if needed
    if (settings->getVersion() != ABEN_SETTINGS_VERSION) {
        Serial.println("applying default app settings!");
        settingsStorage->loadDefault();
    }
}

void Installation::saveToEEPROM() {
    settingsStorage->save();
}

void Installation::loadDefaultSettings() {
    settingsStorage->loadDefault();
}

void Installation::timedLoop() {
    TimeBasedController::timedLoop();

    // update portals
    for (auto i = 0; i < getSize(); i++) {
        getPortal(i)->update();
        getPortal(i)->updateActivation(settings->getPortalActivationTime());
    }

    // autosave
    if (settings->isAutoSave() && autoSaveTimer->elapsed()) {
        saveToEEPROM();
    }
}

AppSettings *Installation::getSettings() {
    return settings;
}
