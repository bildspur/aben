#ifndef TIL_INSTALLATION_H
#define TIL_INSTALLATION_H

#include <EEPROM.h>
#include <assert.h>
#include <controller/TimeBasedController.h>
#include "model/Portal.h"
#include "EEPROM.h"
#include "AppSettings.h"

#define EEPROM_SIZE 0xFF
#define EEPROM_START_ADDRESS 0x00

typedef Portal *PortalPtr;

class Installation : public TimeBasedController {
private:
    PortalPtr *portals;

    uint16_t size;

    AppSettings settings;

public:
    Installation(uint16_t size, PortalPtr *portals);

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

    AppSettings &getSettings();
};


#endif //TIL_INSTALLATION_H
