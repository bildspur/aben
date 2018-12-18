//
// Created by Florian Bruggisser on 17.12.18.
//

#include "OSCRule.h"

OSCRule::OSCRule(const char *address) : address(address) {

}

const char *OSCRule::getAddress() const {
    return address;
}
