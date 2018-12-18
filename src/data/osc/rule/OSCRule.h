//
// Created by Florian Bruggisser on 17.12.18.
//

#ifndef ABEN_OSCRULE_H
#define ABEN_OSCRULE_H


#include <WString.h>
#include <OSCMessage.h>
#include <data/osc/IOSCPublisher.h>

class OSCRule {
private:
    const char *address;

public:
    virtual void receive(IOSCPublisher *publisher, OSCMessage &msg) = 0;

    virtual void publish(IOSCPublisher *publisher) = 0;

    explicit OSCRule(const char *address);

    const char *getAddress() const;
};


#endif //ABEN_OSCRULE_H
