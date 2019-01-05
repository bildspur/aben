//
// Created by Florian Bruggisser on 29.10.18.
//

#ifndef TIL_APPSETTINGS_H
#define TIL_APPSETTINGS_H

#include <cstdint>

#define ABEN_SETTINGS_VERSION 1010

#define APP_FRAME_RATE 30L

struct AppSettings {
private:
    int version = ABEN_SETTINGS_VERSION;

    // global render settings
    unsigned long appFrameRate = APP_FRAME_RATE;

    float minThreshold = 60.0f;

    int portalId = -1;

public:
    int getVersion() const;

    unsigned long getAppFrameRate() const;

    float getMinThreshold() const;

    void setMinThreshold(float minThreshold);

    int getPortalId() const;

    void setPortalId(int portalId);
};


#endif //TIL_APPSETTINGS_H
