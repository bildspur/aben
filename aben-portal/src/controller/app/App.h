#ifndef TIL_INSTALLATION_H
#define TIL_INSTALLATION_H

#include <EEPROM.h>
#include <assert.h>
#include <controller/TimeBasedController.h>
#include "model/Portal.h"
#include "EEPROM.h"
#include "model/AppSettings.h"

#define EEPROM_SIZE 0xFF
#define EEPROM_START_ADDRESS 0x00

typedef Portal *PortalPtr;

class App : public TimeBasedController {
private:
    AppSettings settings;

public:
    App();

    void timedLoop() override;

    void loadFromEEPROM();

    void saveToEEPROM();

    void loadDefaultSettings();

    AppSettings &getSettings();
};


#endif //TIL_INSTALLATION_H
