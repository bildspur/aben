//
// Created by Florian on 30.11.17.
//

#include "App.h"
#include "util/MathUtils.h"

App::App() :
        TimeBasedController(APP_FRAME_RATE, FRAMES_PER_SECOND) {
    this->settings = AppSettings();
}

void App::loadFromEEPROM() {
    EEPROM.begin(EEPROM_SIZE);

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

void App::saveToEEPROM() {
    EEPROM.begin(EEPROM_SIZE);

    // set start address
    int address = EEPROM_START_ADDRESS;
    EEPROM.put(address, settings);

    EEPROM.commit();
    EEPROM.end();
}

AppSettings &App::getSettings() {
    return settings;
}

void App::loadDefaultSettings() {
    settings = AppSettings();
}

void App::timedLoop() {
    TimeBasedController::timedLoop();
}
