//
// Created by Florian Bruggisser on 02.12.18.
//

#ifndef ABEN_PORTAL_PINREADER_H
#define ABEN_PORTAL_PINREADER_H

#import "Arduino.h"

class PinReader {
protected:
    PinReader();

public:
    static unsigned short read3BitEncoder(uint8_t p0, uint8_t p1, uint8_t p2, bool setupPins = true);
};


#endif //ABEN_PORTAL_PINREADER_H
