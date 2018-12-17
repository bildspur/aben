//
// Created by Florian Bruggisser on 17.12.18.
//

#include "OSCRule.h"

OSCRule::OSCRule(const char *address) {
    this->address = address;
}

OSCRule::OSCRule(String address) {
    this->address = address.c_str();
}

const char *OSCRule::getAddress() const {
    return address;
}
