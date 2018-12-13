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

unsigned long AppSettings::getActivatedDoorStats() const {
    return activatedDoorStats;
}

void AppSettings::setActivatedDoorStats(unsigned long activatedDoorStats) {
    AppSettings::activatedDoorStats = activatedDoorStats;
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

void AppSettings::incActivatedDoorStats() {
    activatedDoorStats++;
}

unsigned long AppSettings::getAutoSaveTime() const {
    return autoSaveTime;
}

void AppSettings::setAutoSaveTime(unsigned long autoSaveTime) {
    AppSettings::autoSaveTime = autoSaveTime;
}
