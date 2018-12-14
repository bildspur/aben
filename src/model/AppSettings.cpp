//
// Created by Florian Bruggisser on 29.10.18.
//

#include "AppSettings.h"

float AppSettings::getMinBrightness() const {
    return minBrightness;
}

void AppSettings::setMinBrightness(float minBrightness) {
    AppSettings::minBrightness = minBrightness;
}

float AppSettings::getMaxBrightness() const {
    return maxBrightness;
}

void AppSettings::setMaxBrightness(float maxBrightness) {
    AppSettings::maxBrightness = maxBrightness;
}

unsigned long AppSettings::getTimeStarMinDuration() const {
    return timeStarMinDuration;
}

void AppSettings::setTimeStarMinDuration(unsigned long timeStarMinDuration) {
    AppSettings::timeStarMinDuration = timeStarMinDuration;
}

unsigned long AppSettings::getTimeStarMaxDuration() const {
    return timeStarMaxDuration;
}

void AppSettings::setTimeStarMaxDuration(unsigned long timeStarMaxDuration) {
    AppSettings::timeStarMaxDuration = timeStarMaxDuration;
}

float AppSettings::getTimeStarRandomOnFactor() const {
    return timeStarRandomOnFactor;
}

void AppSettings::setTimeStarRandomOnFactor(float timeStarRandomOnFactor) {
    AppSettings::timeStarRandomOnFactor = timeStarRandomOnFactor;
}

float AppSettings::getTimeStarMinBrightness() const {
    return timeStarMinBrightness;
}

void AppSettings::setTimeStarMinBrightness(float timeStarMinBrightness) {
    AppSettings::timeStarMinBrightness = timeStarMinBrightness;
}

float AppSettings::getTimeStarMaxBrightness() const {
    return timeStarMaxBrightness;
}

void AppSettings::setTimeStarMaxBrightness(float timeStarMaxBrightness) {
    AppSettings::timeStarMaxBrightness = timeStarMaxBrightness;
}

int AppSettings::getVersion() const {
    return version;
}

bool AppSettings::isGammaCorrection() const {
    return gammaCorrection;
}

void AppSettings::setGammaCorrection(bool gammaCorrection) {
    AppSettings::gammaCorrection = gammaCorrection;
}

unsigned long AppSettings::getAppFrameRate() const {
    return appFrameRate;
}

float AppSettings::getPortalMinTreshold() const {
    return portalMinTreshold;
}

void AppSettings::setPortalMinTreshold(float portalMinTreshold) {
    AppSettings::portalMinTreshold = portalMinTreshold;
}

float AppSettings::getDefaultHue() const {
    return defaultHue;
}

void AppSettings::setDefaultHue(float defaultHue) {
    AppSettings::defaultHue = defaultHue;
}

float AppSettings::getDefaultSaturation() const {
    return defaultSaturation;
}

void AppSettings::setDefaultSaturation(float defaultSaturation) {
    AppSettings::defaultSaturation = defaultSaturation;
}

unsigned long AppSettings::getPortalActivationTime() const {
    return portalActivationTime;
}

void AppSettings::setPortalActivationTime(unsigned long doorActivationTime) {
    AppSettings::portalActivationTime = doorActivationTime;
}

bool AppSettings::isInteractionOn() const {
    return interactionOn;
}

void AppSettings::setInteractionOn(bool interactionOn) {
    AppSettings::interactionOn = interactionOn;
}

unsigned long AppSettings::getShowSpeed() const {
    return showSpeed;
}

void AppSettings::setShowSpeed(unsigned long showSpeed) {
    AppSettings::showSpeed = showSpeed;
}

bool AppSettings::isRainbowMode() const {
    return rainbowMode;
}

void AppSettings::setRainbowMode(bool rainbowMode) {
    AppSettings::rainbowMode = rainbowMode;
}

float AppSettings::getRainbowStart() const {
    return rainbowStart;
}

void AppSettings::setRainbowStart(float rainbowStart) {
    AppSettings::rainbowStart = rainbowStart;
}

float AppSettings::getRainbowEnd() const {
    return rainbowEnd;
}

void AppSettings::setRainbowEnd(float rainbowEnd) {
    AppSettings::rainbowEnd = rainbowEnd;
}

unsigned long AppSettings::getRainbowTime() const {
    return rainbowTime;
}

void AppSettings::setRainbowTime(unsigned long rainbowTime) {
    AppSettings::rainbowTime = rainbowTime;
}

bool AppSettings::isAutoSave() const {
    return autoSave;
}

void AppSettings::setAutoSave(bool autoSave) {
    AppSettings::autoSave = autoSave;
}

unsigned long AppSettings::getActivatedPortalStats() const {
    return activatedPortalStats;
}

void AppSettings::setActivatedPortalStats(unsigned long activatedDoorStats) {
    AppSettings::activatedPortalStats = activatedDoorStats;
}

unsigned long AppSettings::getActivatedShowStats() const {
    return activatedShowStats;
}

void AppSettings::setActivatedShowStats(unsigned long activatedShowStats) {
    AppSettings::activatedShowStats = activatedShowStats;
}

void AppSettings::incActivatedShowStats() {
    activatedShowStats++;
}

unsigned long AppSettings::getAutoSaveTime() const {
    return autoSaveTime;
}

void AppSettings::setAutoSaveTime(unsigned long autoSaveTime) {
    AppSettings::autoSaveTime = autoSaveTime;
}

unsigned int AppSettings::getMinPortalToActivate() const {
    return minPortalToActivate;
}

void AppSettings::setMinPortalToActivate(unsigned int minPortalToActivate) {
    AppSettings::minPortalToActivate = minPortalToActivate;
}

unsigned int AppSettings::getStatsPortal0() const {
    return statsPortal0;
}

void AppSettings::setStatsPortal0(unsigned int statsPortal0) {
    AppSettings::statsPortal0 = statsPortal0;
}

unsigned int AppSettings::getStatsPortal1() const {
    return statsPortal1;
}

void AppSettings::setStatsPortal1(unsigned int statsPortal1) {
    AppSettings::statsPortal1 = statsPortal1;
}

unsigned int AppSettings::getStatsPortal2() const {
    return statsPortal2;
}

void AppSettings::setStatsPortal2(unsigned int statsPortal2) {
    AppSettings::statsPortal2 = statsPortal2;
}

unsigned int AppSettings::getStatsPortal3() const {
    return statsPortal3;
}

void AppSettings::setStatsPortal3(unsigned int statsPortal3) {
    AppSettings::statsPortal3 = statsPortal3;
}

unsigned int AppSettings::getStatsPortal4() const {
    return statsPortal4;
}

void AppSettings::setStatsPortal4(unsigned int statsPortal4) {
    AppSettings::statsPortal4 = statsPortal4;
}

void AppSettings::incActivatedPortalStats(unsigned int index) {
    activatedPortalStats++;

    if (index == 0)
        statsPortal0++;

    if (index == 1)
        statsPortal1++;

    if (index == 2)
        statsPortal2++;

    if (index == 3)
        statsPortal3++;

    if (index == 4)
        statsPortal4++;
}
