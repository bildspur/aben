//
// Created by Florian Bruggisser on 29.10.18.
//

#ifndef TIL_APPSETTINGS_H
#define TIL_APPSETTINGS_H

#define ABEN_SETTINGS_VERSION 1001

#define APP_FRAME_RATE 60L

struct AppSettings {
private:
    int version = ABEN_SETTINGS_VERSION;

    // global render settings
    unsigned long appFrameRate = APP_FRAME_RATE;

    float minThreshold = 30.0f;

public:
    int getVersion() const;

    unsigned long getAppFrameRate() const;

    float getMinThreshold() const;

    void setMinThreshold(float minThreshold);
};


#endif //TIL_APPSETTINGS_H
