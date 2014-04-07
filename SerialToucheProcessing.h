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
#include "Grid.h"
#include <iostream>

struct commandData{
    u_int8_t control_zero;
    u_int8_t command;
    u_int8_t upper_x;
    u_int8_t lower_x;
    u_int8_t upper_y;
    u_int8_t lower_y;
    u_int8_t zeroByte;
    u_int8_t checkSum;
};
class SerialToucheProcessing : public SerialProcessings{
public:
    SerialToucheProcessing(Grid* g);
    void process(size_char_tab data);
    void setActive(bool active);
private:
    bool isCheckSumOk(commandData* strucData);
    commandData* strucData;
    size_t mSize;
    short unsigned int  mReceivedData [8];
    Grid* mGrid;
    void formatDataAndSetInput( commandData* strucData);
};
#endif /* defined(__LibLoAndCap__SerialToucheProcessing__) */
