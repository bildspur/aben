//
// Created by Florian Bruggisser on 29.10.18.
//

#include <data/osc/rule/OSCDataBinding.h>
#include "AppSettings.h"

AppSettings::AppSettings(OSCDataRouter *oscDataRouter, EEPROMStorage *eepromStorage) {
    // eeprom
    eepromStorage->add(&version);
    //eepromStorage->add(&appFrameRate);
    eepromStorage->add(&minBrightness);
    eepromStorage->add(&maxBrightness);
    eepromStorage->add(&gammaCorrection);
    eepromStorage->add(&autoSave);
    eepromStorage->add(&autoSaveTime);
    eepromStorage->add(&activatedPortalStats);
    eepromStorage->add(&activatedShowStats);

    eepromStorage->add(&statsPortal0);
    eepromStorage->add(&statsPortal1);
    eepromStorage->add(&statsPortal2);
    eepromStorage->add(&statsPortal3);
    eepromStorage->add(&statsPortal4);

    eepromStorage->add(&timeStarMinDuration);
    eepromStorage->add(&timeStarMaxDuration);
    eepromStorage->add(&timeStarRandomOnFactor);
    eepromStorage->add(&timeStarMinBrightness);
    eepromStorage->add(&timeStarMaxBrightness);
    eepromStorage->add(&portalMinTreshold);
    eepromStorage->add(&defaultHue);
    eepromStorage->add(&defaultSaturation);
    eepromStorage->add(&rainbowMode);
    eepromStorage->add(&rainbowTime);
    eepromStorage->add(&rainbowStart);
    eepromStorage->add(&rainbowEnd);
    eepromStorage->add(&portalActivationTime);
    eepromStorage->add(&interactionOn);
    eepromStorage->add(&showSpeed);
    eepromStorage->add(&minPortalToActivate);

    // osc
    oscDataRouter->addRule(new OSCDataBinding("/aben/version", &version, true));
    oscDataRouter->addRule(new OSCDataBinding("/aben/framerate", &appFrameRate, true));
    oscDataRouter->addRule(new OSCDataBinding("/aben/brightness/min", &minBrightness, true));
    oscDataRouter->addRule(new OSCDataBinding("/aben/brightness/max", &maxBrightness, true));
    oscDataRouter->addRule(new OSCDataBinding("/aben/gamma/on", &gammaCorrection, true));
    oscDataRouter->addRule(new OSCDataBinding("/aben/autosave/on", &autoSave, true));
    oscDataRouter->addRule(new OSCDataBinding("/aben/autosave/time", &autoSaveTime, true));

    oscDataRouter->addRule(new OSCDataBinding("/aben/stats/portals", &activatedPortalStats, true));
    oscDataRouter->addRule(new OSCDataBinding("/aben/stats/shows", &activatedShowStats, true));
    oscDataRouter->addRule(new OSCDataBinding("/aben/stats/portal/0", &statsPortal0, true));
    oscDataRouter->addRule(new OSCDataBinding("/aben/stats/portal/1", &statsPortal1, true));
    oscDataRouter->addRule(new OSCDataBinding("/aben/stats/portal/2", &statsPortal2, true));
    oscDataRouter->addRule(new OSCDataBinding("/aben/stats/portal/3", &statsPortal3, true));
    oscDataRouter->addRule(new OSCDataBinding("/aben/stats/portal/4", &statsPortal4, true));

    oscDataRouter->addRule(new OSCDataBinding("/aben/timestar/brightness/min", &timeStarMinDuration, true));
    oscDataRouter->addRule(new OSCDataBinding("/aben/timestar/brightness/max", &timeStarMaxDuration, true));
    oscDataRouter->addRule(new OSCDataBinding("/aben/timestar/randomFactor", &timeStarRandomOnFactor, true));
    oscDataRouter->addRule(new OSCDataBinding("/aben/timestar/brightness/min", &timeStarMinBrightness, true));
    oscDataRouter->addRule(new OSCDataBinding("/aben/timestar/brightness/max", &timeStarMaxBrightness, true));
    oscDataRouter->addRule(new OSCDataBinding("/aben/portal/threshold", &portalMinTreshold, true));
    oscDataRouter->addRule(new OSCDataBinding("/aben/color/hue", &defaultHue, true));
    oscDataRouter->addRule(new OSCDataBinding("/aben/color/saturation", &defaultSaturation, true));
    oscDataRouter->addRule(new OSCDataBinding("/aben/rainbow/on", &rainbowMode, true));
    oscDataRouter->addRule(new OSCDataBinding("/aben/rainbow/time", &rainbowTime, true));
    oscDataRouter->addRule(new OSCDataBinding("/aben/rainbow/start", &rainbowStart, true));
    oscDataRouter->addRule(new OSCDataBinding("/aben/rainbow/end", &rainbowEnd, true));
    oscDataRouter->addRule(new OSCDataBinding("/aben/activationtime", &portalActivationTime, true));
    oscDataRouter->addRule(new OSCDataBinding("/aben/interaction/on", &interactionOn, true));
    oscDataRouter->addRule(new OSCDataBinding("/aben/show/speed", &showSpeed, true));
    oscDataRouter->addRule(new OSCDataBinding("/aben/show/minportal", &minPortalToActivate, true));
}

float AppSettings::getMinBrightness() const {
    return minBrightness.get();
}

void AppSettings::setMinBrightness(float minBrightness) {
    AppSettings::minBrightness.set(minBrightness);
}

float AppSettings::getMaxBrightness() const {
    return maxBrightness.get();
}

void AppSettings::setMaxBrightness(float maxBrightness) {
    AppSettings::maxBrightness.set(maxBrightness);
}

unsigned long AppSettings::getTimeStarMinDuration() const {
    return timeStarMinDuration.get();
}

void AppSettings::setTimeStarMinDuration(unsigned long timeStarMinDuration) {
    AppSettings::timeStarMinDuration.set(timeStarMinDuration);
}

unsigned long AppSettings::getTimeStarMaxDuration() const {
    return timeStarMaxDuration.get();
}

void AppSettings::setTimeStarMaxDuration(unsigned long timeStarMaxDuration) {
    AppSettings::timeStarMaxDuration.set(timeStarMaxDuration);
}

float AppSettings::getTimeStarRandomOnFactor() const {
    return timeStarRandomOnFactor.get();
}

void AppSettings::setTimeStarRandomOnFactor(float timeStarRandomOnFactor) {
    AppSettings::timeStarRandomOnFactor.set(timeStarRandomOnFactor);
}

float AppSettings::getTimeStarMinBrightness() const {
    return timeStarMinBrightness.get();
}

void AppSettings::setTimeStarMinBrightness(float timeStarMinBrightness) {
    AppSettings::timeStarMinBrightness.set(timeStarMinBrightness);
}

float AppSettings::getTimeStarMaxBrightness() const {
    return timeStarMaxBrightness.get();
}

void AppSettings::setTimeStarMaxBrightness(float timeStarMaxBrightness) {
    AppSettings::timeStarMaxBrightness.set(timeStarMaxBrightness);
}

int AppSettings::getVersion() const {
    return version.get();
}

bool AppSettings::isGammaCorrection() const {
    return gammaCorrection.get();
}

void AppSettings::setGammaCorrection(bool gammaCorrection) {
    AppSettings::gammaCorrection.set(gammaCorrection);
}

unsigned long AppSettings::getAppFrameRate() const {
    return appFrameRate.get();
}

float AppSettings::getPortalMinTreshold() const {
    return portalMinTreshold.get();
}

void AppSettings::setPortalMinTreshold(float portalMinTreshold) {
    AppSettings::portalMinTreshold.set(portalMinTreshold);
}

float AppSettings::getDefaultHue() const {
    return defaultHue.get();
}

void AppSettings::setDefaultHue(float defaultHue) {
    AppSettings::defaultHue.set(defaultHue);
}

float AppSettings::getDefaultSaturation() const {
    return defaultSaturation.get();
}

void AppSettings::setDefaultSaturation(float defaultSaturation) {
    AppSettings::defaultSaturation.set(defaultSaturation);
}

unsigned long AppSettings::getPortalActivationTime() const {
    return portalActivationTime.get();
}

void AppSettings::setPortalActivationTime(unsigned long doorActivationTime) {
    AppSettings::portalActivationTime.set(doorActivationTime);
}

bool AppSettings::isInteractionOn() const {
    return interactionOn.get();
}

void AppSettings::setInteractionOn(bool interactionOn) {
    AppSettings::interactionOn.set(interactionOn);
}

unsigned long AppSettings::getShowSpeed() const {
    return showSpeed.get();
}

void AppSettings::setShowSpeed(unsigned long showSpeed) {
    AppSettings::showSpeed.set(showSpeed);
}

bool AppSettings::isRainbowMode() const {
    return rainbowMode.get();
}

void AppSettings::setRainbowMode(bool rainbowMode) {
    AppSettings::rainbowMode.set(rainbowMode);
}

float AppSettings::getRainbowStart() const {
    return rainbowStart.get();
}

void AppSettings::setRainbowStart(float rainbowStart) {
    AppSettings::rainbowStart.set(rainbowStart);
}

float AppSettings::getRainbowEnd() const {
    return rainbowEnd.get();
}

void AppSettings::setRainbowEnd(float rainbowEnd) {
    AppSettings::rainbowEnd.set(rainbowEnd);
}

unsigned long AppSettings::getRainbowTime() const {
    return rainbowTime.get();
}

void AppSettings::setRainbowTime(unsigned long rainbowTime) {
    AppSettings::rainbowTime.set(rainbowTime);
}

bool AppSettings::isAutoSave() const {
    return autoSave.get();
}

void AppSettings::setAutoSave(bool autoSave) {
    AppSettings::autoSave.set(autoSave);
}

unsigned long AppSettings::getActivatedPortalStats() const {
    return activatedPortalStats.get();
}

void AppSettings::setActivatedPortalStats(unsigned long activatedDoorStats) {
    AppSettings::activatedPortalStats.set(activatedDoorStats);
}

unsigned long AppSettings::getActivatedShowStats() const {
    return activatedShowStats.get();
}

void AppSettings::setActivatedShowStats(unsigned long activatedShowStats) {
    AppSettings::activatedShowStats.set(activatedShowStats);
}

void AppSettings::incActivatedShowStats() {
    activatedShowStats.set(activatedShowStats.get() + 1);
}

unsigned long AppSettings::getAutoSaveTime() const {
    return autoSaveTime.get();
}

void AppSettings::setAutoSaveTime(unsigned long autoSaveTime) {
    AppSettings::autoSaveTime.set(autoSaveTime);
}

unsigned int AppSettings::getMinPortalToActivate() const {
    return minPortalToActivate.get();
}

void AppSettings::setMinPortalToActivate(unsigned int minPortalToActivate) {
    AppSettings::minPortalToActivate.set(minPortalToActivate);
}

unsigned int AppSettings::getStatsPortal0() const {
    return statsPortal0.get();
}

void AppSettings::setStatsPortal0(unsigned int statsPortal0) {
    AppSettings::statsPortal0.set(statsPortal0);
}

unsigned int AppSettings::getStatsPortal1() const {
    return statsPortal1.get();
}

void AppSettings::setStatsPortal1(unsigned int statsPortal1) {
    AppSettings::statsPortal1.set(statsPortal1);
}

unsigned int AppSettings::getStatsPortal2() const {
    return statsPortal2.get();
}

void AppSettings::setStatsPortal2(unsigned int statsPortal2) {
    AppSettings::statsPortal2.set(statsPortal2);
}

unsigned int AppSettings::getStatsPortal3() const {
    return statsPortal3.get();
}

void AppSettings::setStatsPortal3(unsigned int statsPortal3) {
    AppSettings::statsPortal3.set(statsPortal3);
}

unsigned int AppSettings::getStatsPortal4() const {
    return statsPortal4.get();
}

void AppSettings::setStatsPortal4(unsigned int statsPortal4) {
    AppSettings::statsPortal4.set(statsPortal4);
}

void AppSettings::incActivatedPortalStats(unsigned int index) {
    activatedPortalStats.set(activatedPortalStats.get() + 1);

    if (index == 0)
        statsPortal0.set(statsPortal0.get() + 1);

    if (index == 1)
        statsPortal1.set(statsPortal1.get() + 1);

    if (index == 2)
        statsPortal2.set(statsPortal2.get() + 1);

    if (index == 3)
        statsPortal3.set(statsPortal3.get() + 1);

    if (index == 4)
        statsPortal4.set(statsPortal4.get() + 1);
}