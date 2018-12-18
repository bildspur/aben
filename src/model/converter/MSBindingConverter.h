//
// Created by Florian Bruggisser on 18.12.18.
//

#ifndef ABEN_MSBINDINGCONVERTER_H
#define ABEN_MSBINDINGCONVERTER_H


#include <data/osc/rule/converter/IOSCBindingConverter.h>

class MSBindingConverter : public IOSCBindingConverter {
public:
    float convertInput(float value) override;

    float convertOutput(float value) override;
};


#endif //ABEN_MSBINDINGCONVERTER_H
