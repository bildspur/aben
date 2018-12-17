//
// Created by Florian Bruggisser on 17.12.18.
//

#ifndef ABEN_IOSCPUBLISHER_H
#define ABEN_IOSCPUBLISHER_H


#include <OSCMessage.h>

class IOSCPublisher {
public:
    virtual void sendMessage(OSCMessage &msg) = 0;
};


#endif //ABEN_IOSCPUBLISHER_H
