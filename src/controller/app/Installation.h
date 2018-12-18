#ifndef TIL_INSTALLATION_H
#define TIL_INSTALLATION_H

#include <EEPROM.h>
#include <assert.h>
#include <controller/TimeBasedController.h>
#include <data/osc/OSCDataRouter.h>
#include <data/eeprom/EEPROMStorage.h>
#include "model/Portal.h"
#include "EEPROM.h"
#include "model/AppSettings.h"

#define EEPROM_SIZE 1024
#define EEPROM_START_ADDRESS 0x00

typedef Portal *PortalPtr;

class Installation : public TimeBasedController {
private:
    PortalPtr *portals;

    uint16_t size;

    AppSettings *settings;

    Timer *autoSaveTimer;

    OSCDataRouter *oscDataRouter;

    EEPROMStorage *settingsStorage;

    EEPROMStorage *statsStorage;

public:
    Installation(uint16_t size, PortalPtr *portals, OSCDataRouter *oscDataRouter);

    void timedLoop() override;

    uint16_t getSize();

    PortalPtr *getPortals();

    PortalPtr getPortal(uint16_t index);

    PortalPtr getPortal(int index);

    void initPortals();

    void loadFromEEPROM();

    void saveToEEPROM();

    void loadDefaultSettings();

    void turnOn();

    void turnOff();

    AppSettings *getSettings();

    void resetStats();
};


#endif //TIL_INSTALLATION_H
