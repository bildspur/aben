//
// Created by Florian Bruggisser on 17.12.18.
//

#ifndef ABEN_EEPROMSTORAGE_H
#define ABEN_EEPROMSTORAGE_H

#undef min
#undef max

#include <vector>
#include "IEEPROMDataModel.h"

class EEPROMStorage {
private:
    typedef IEEPROMDataModel *DataModelPtr;

    std::vector<DataModelPtr> dataModels;

    unsigned int eepromSize;
    unsigned int eepromStartAddress;

public:
    explicit EEPROMStorage(unsigned int eepromStartAddress = 0x0, unsigned int eepromSize = 1024);

    void save();

    void load();

    void loadDefault();

    void add(DataModelPtr dataModel);
};


#endif //ABEN_EEPROMSTORAGE_H
