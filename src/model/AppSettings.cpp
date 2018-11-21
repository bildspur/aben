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
