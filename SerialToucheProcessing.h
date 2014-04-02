//
//  SerialToucheProcessing.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 2/04/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__SerialToucheProcessing__
#define __LibLoAndCap__SerialToucheProcessing__


#include "SerialProcessings.h"
#include <iostream>

struct commandData{
    char control_zero;
    char command;
    char upper_x;
    char lower_x;
    char upper_y;
    char lower_y;
    char zeroByte;
    char checkSum;
};
class SerialToucheProcessing : public SerialProcessings{
public:
    SerialToucheProcessing();
    void process(size_char_tab data);
    void setActive(bool active);
private:
    commandData* strucData;
    size_t mSize;
    int mSerialCount;
    short unsigned int  mReceivedData [8];
};
#endif /* defined(__LibLoAndCap__SerialToucheProcessing__) */
