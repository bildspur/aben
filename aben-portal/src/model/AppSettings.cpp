//
// Created by Florian Bruggisser on 29.10.18.
//

#include "AppSettings.h"


int AppSettings::getVersion() const {
    return version;
}

unsigned long AppSettings::getAppFrameRate() const {
    return appFrameRate;
}

float AppSettings::getMinThreshold() const {
    return minThreshold;
}

void AppSettings::setMinThreshold(float minThreshold) {
    AppSettings::minThreshold = minThreshold;
}

int AppSettings::getPortalId() const {
    return portalId;
}

void AppSettings::setPortalId(int portalId) {
    AppSettings::portalId = portalId;
}
