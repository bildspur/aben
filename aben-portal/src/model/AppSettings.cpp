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