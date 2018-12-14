//
// Created by Florian Bruggisser on 29.10.18.
//

#ifndef TIL_APPSETTINGS_H
#define TIL_APPSETTINGS_H

#define ABEN_SETTINGS_VERSION 1012

#define APP_FRAME_RATE 60L

struct AppSettings {
private:
    int version = ABEN_SETTINGS_VERSION;

    // global render settings
    unsigned long appFrameRate = APP_FRAME_RATE;

    float minBrightness = 0.0f;

    float maxBrightness = 1.0f;

    bool gammaCorrection = true;

    bool autoSave = true;

    unsigned long autoSaveTime = 30 * 60 * 1000;

    // stats
    unsigned int activatedPortalStats = 0;

    unsigned int activatedShowStats = 0;

    unsigned int statsPortal0 = 0;

    unsigned int statsPortal1 = 0;

    unsigned int statsPortal2 = 0;

    unsigned int statsPortal3 = 0;

    unsigned int statsPortal4 = 0;

    // time star scene settings
    unsigned long timeStarMinDuration = 1500L; // used for portal scene as timer

    unsigned long timeStarMaxDuration = 5000L;

    float timeStarRandomOnFactor = 0.99f;

    float timeStarMinBrightness = 0.4f;

    float timeStarMaxBrightness = 0.8f;

    float portalMinTreshold = 60.0;

    // keyPoints
    float defaultHue = 200.0;

    float defaultSaturation = 0.8f;

    bool rainbowMode = true;

    unsigned long rainbowTime = 20 * 1000;

    float rainbowStart = 180.0f;

    float rainbowEnd = 30.0f;

    // installation
    unsigned long portalActivationTime = 15000L;

    bool interactionOn = true;

    unsigned long showSpeed = 1000L;

    unsigned int minPortalToActivate = 3;


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

    unsigned long getShowSpeed() const;

    void setShowSpeed(unsigned long showSpeed);

    bool isRainbowMode() const;

    void setRainbowMode(bool rainbowMode);

    float getRainbowStart() const;

    void setRainbowStart(float rainbowStart);

    float getRainbowEnd() const;

    void setRainbowEnd(float rainbowEnd);

    unsigned long getRainbowTime() const;

    void setRainbowTime(unsigned long rainbowTime);

    bool isAutoSave() const;

    void setAutoSave(bool autoSave);

    unsigned long getActivatedPortalStats() const;

    void setActivatedPortalStats(unsigned long activatedDoorStats);

    unsigned long getActivatedShowStats() const;

    void setActivatedShowStats(unsigned long activatedShowStats);

    void incActivatedShowStats();

    void incActivatedPortalStats(unsigned int index);

    unsigned long getAutoSaveTime() const;

    void setAutoSaveTime(unsigned long autoSaveTime);

    unsigned int getMinPortalToActivate() const;

    void setMinPortalToActivate(unsigned int minPortalToActivate);

    unsigned int getStatsPortal0() const;

    void setStatsPortal0(unsigned int statsPortal0);

    unsigned int getStatsPortal1() const;

    void setStatsPortal1(unsigned int statsPortal1);

    unsigned int getStatsPortal2() const;

    void setStatsPortal2(unsigned int statsPortal2);

    unsigned int getStatsPortal3() const;

    void setStatsPortal3(unsigned int statsPortal3);

    unsigned int getStatsPortal4() const;

    void setStatsPortal4(unsigned int statsPortal4);
};


#endif //TIL_APPSETTINGS_H
