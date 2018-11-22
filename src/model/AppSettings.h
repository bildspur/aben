//
// Created by Florian Bruggisser on 29.10.18.
//

#ifndef TIL_APPSETTINGS_H
#define TIL_APPSETTINGS_H

#define ABEN_SETTINGS_VERSION 1003

struct AppSettings {
private:
    int version = ABEN_SETTINGS_VERSION;

    // global render settings
    unsigned long appFrameRate = 60L;

    float minBrightness = 0.0f;

    float maxBrightness = 1.0f;

    bool gammaCorrection = true;

    // time star scene settings
    unsigned long timeStarMinDuration = 3000L;

    unsigned long timeStarMaxDuration = 5000L;

    float timeStarRandomOnFactor = 0.99f;

    float timeStarMinBrightness = 0.0f;

    float timeStarMaxBrightness = 1.0f;

public:
    int getVersion() const;

    unsigned long getAppFrameRate() const;

    float getMinBrightness() const;

    void setMinBrightness(float minBrightness);

    float getMaxBrightness() const;

    void setMaxBrightness(float maxBrightness);

    bool isGammaCorrection() const;

    void setGammaCorrection(bool gammaCorrection);

    unsigned long getTimeStarMinDuration() const;

    void setTimeStarMinDuration(unsigned long timeStarMinDuration);

    unsigned long getTimeStarMaxDuration() const;

    void setTimeStarMaxDuration(unsigned long timeStarMaxDuration);

    float getTimeStarRandomOnFactor() const;

    void setTimeStarRandomOnFactor(float timeStarRandomOnFactor);

    float getTimeStarMinBrightness() const;

    void setTimeStarMinBrightness(float timeStarMinBrightness);

    float getTimeStarMaxBrightness() const;

    void setTimeStarMaxBrightness(float timeStarMaxBrightness);
};


#endif //TIL_APPSETTINGS_H
