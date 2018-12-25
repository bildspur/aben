//
// Created by Florian Bruggisser on 29.10.18.
//

#ifndef TIL_APPSETTINGS_H
#define TIL_APPSETTINGS_H

#include <data/osc/OSCDataRouter.h>
#include <data/eeprom/EEPROMStorage.h>
#include <data/model/DataModel.h>

#define ABEN_SETTINGS_VERSION 2015

#define APP_FRAME_RATE 60L

class AppSettings {
private:
    DataModel<int> version = DataModel<int>(ABEN_SETTINGS_VERSION);

    // global render settings
    DataModel<unsigned long> appFrameRate = DataModel<unsigned long>(APP_FRAME_RATE);

    DataModel<float> minBrightness = DataModel<float>(0.0f);

    DataModel<float> maxBrightness = DataModel<float>(1.0f);

    DataModel<bool> gammaCorrection = DataModel<bool>(true);

    DataModel<bool> autoSave = DataModel<bool>(true);

    DataModel<unsigned long> autoSaveTime = DataModel<unsigned long>(30 * 60 * 1000);

    // stats
    DataModel<unsigned int> activatedPortalStats = DataModel<unsigned int>(0);

    DataModel<unsigned int> activatedShowStats = DataModel<unsigned int>(0);

    DataModel<unsigned int> statsPortal0 = DataModel<unsigned int>(0);

    DataModel<unsigned int> statsPortal1 = DataModel<unsigned int>(0);

    DataModel<unsigned int> statsPortal2 = DataModel<unsigned int>(0);

    DataModel<unsigned int> statsPortal3 = DataModel<unsigned int>(0);

    DataModel<unsigned int> statsPortal4 = DataModel<unsigned int>(0);

    // time star scene settings
    DataModel<unsigned long> timeStarMinDuration = DataModel<unsigned long>(1500L); // used for portal scene as timer

    DataModel<unsigned long> timeStarMaxDuration = DataModel<unsigned long>(5000L);

    DataModel<float> timeStarRandomOnFactor = DataModel<float>(0.99f);

    DataModel<float> timeStarMinBrightness = DataModel<float>(0.4f);

    DataModel<float> timeStarMaxBrightness = DataModel<float>(0.8f);

    DataModel<float> portalMinTreshold = DataModel<float>(60.0f);

    // keyPoints
    DataModel<float> defaultHue = DataModel<float>(200.0f);

    DataModel<float> defaultSaturation = DataModel<float>(0.8f);

    DataModel<bool> rainbowMode = DataModel<bool>(false);

    DataModel<unsigned long> rainbowTime = DataModel<unsigned long>(20 * 1000);

    DataModel<float> rainbowStart = DataModel<float>(180.0f);

    DataModel<float> rainbowEnd = DataModel<float>(30.0f);

    // installation
    DataModel<unsigned long> portalActivationTime = DataModel<unsigned long>(5 * 1000);

    DataModel<bool> interactionOn = DataModel<bool>(true);

    DataModel<unsigned long> showSpeed = DataModel<unsigned long>(1000L);

    DataModel<unsigned int> minPortalToActivate = DataModel<unsigned int>(3);

    DataModel<bool> sceneControllerOn = DataModel<bool>(true);

public:
    AppSettings(OSCDataRouter *oscDataRouter, EEPROMStorage *eepromStorage, EEPROMStorage *statsStorage);

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

    const bool isSceneControllerOn() const;

    void setSceneControllerOn(bool value);
};


#endif //TIL_APPSETTINGS_H
