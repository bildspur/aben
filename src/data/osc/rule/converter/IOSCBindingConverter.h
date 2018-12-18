//
// Created by Florian Bruggisser on 18.12.18.
//

#ifndef ABEN_IOSCBINDINGCONVERTER_H
#define ABEN_IOSCBINDINGCONVERTER_H


class IOSCBindingConverter {
public:
    virtual float convertInput(float value) = 0;

    virtual float convertOutput(float value) = 0;
};


#endif //ABEN_IOSCBINDINGCONVERTER_H
