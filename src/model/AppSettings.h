//
// Created by Florian Bruggisser on 29.10.18.
//

#ifndef TIL_APPSETTINGS_H
#define TIL_APPSETTINGS_H

#define ABEN_SETTINGS_VERSION 1007

#define APP_FRAME_RATE 60L

struct AppSettings {
private:
    int version = ABEN_SETTINGS_VERSION;

    // global render settings
    unsigned long appFrameRate = APP_FRAME_RATE;

    float minBrightness = 0.0f;

    float maxBrightness = 1.0f;

    bool gammaCorrection = true;

    // time star scene settings
    unsigned long timeStarMinDuration = 3000L;

    unsigned long timeStarMaxDuration = 5000L;

    float timeStarRandomOnFactor = 0.99f;

    float timeStarMinBrightness = 0.0f;

    float timeStarMaxBrightness = 1.0f;

    float portalMinTreshold = 60.0;

    // colors
    float defaultHue = 200.0;

    float defaultSaturation = 0.8f;

    // installation
    unsigned long portalActivationTime = 10000L;

    bool interactionOn = true;


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

    float getPortalMinTreshold() const;

    void setPortalMinTreshold(float portalMinTreshold);

    float getDefaultHue() const;

    void setDefaultHue(float defaultHue);

    float getDefaultSaturation() const;

    void setDefaultSaturation(float defaultSaturation);

    unsigned long getPortalActivationTime() const;

    void setPortalActivationTime(unsigned long doorActivationTime);

    bool isInteractionOn() const;

    void setInteractionOn(bool interactionOn);
};


#endif //TIL_APPSETTINGS_H
