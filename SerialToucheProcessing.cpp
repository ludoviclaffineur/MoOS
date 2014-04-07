//
//  SerialToucheProcessing.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 2/04/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "SerialToucheProcessing.h"
#include <sstream>

SerialToucheProcessing::SerialToucheProcessing(Grid* g){
    mGrid = g;
    for (int i = 0; i<=159; i++) {
        std::stringstream name;
        name<< i ;
        mGrid->addInput(name.str().c_str(), 0, 1024, -1, 0, Converter::LINEAR);
    }
}

void SerialToucheProcessing::process(size_char_tab data){
    for (int i =0;i<data.size;i++){
        if (*data.tab ==0){
            strucData = (commandData*) data.tab;
            //printf("DAAAR BEN IK, %d \n", strucData->command);
            switch (strucData->command) {
                case 1:
                    if(isCheckSumOk(strucData)){
                        formatDataAndSetInput( strucData);
                    }
                    break;
                case 2:
                    mGrid->compute();
                default:
                    break;
            }
            data.tab += 7 ;
            i+=7;
        }
        data.tab++;
    }
}

bool SerialToucheProcessing::isCheckSumOk(commandData* strucData){
    u_int8_t checksum=0;
    checksum+= (strucData->control_zero +
                strucData->command +
                strucData->upper_x +
                strucData->lower_x +
                strucData->upper_y +
                strucData->lower_y +
                strucData->zeroByte)%255;
    return (checksum == strucData->checkSum);
}

void SerialToucheProcessing::setActive( bool active ) {
    mActive = active;
}

void SerialToucheProcessing::formatDataAndSetInput( commandData* strucData){
    u_int16_t x = 0;
    u_int16_t y = 0;

    if (((u_int8_t)strucData->zeroByte & 0x08) == 0x08){
        strucData->upper_y = 0;
    }
    if (((u_int8_t)strucData->zeroByte & 0x04) == 0x04){
        strucData->lower_y = 0;
    }
    if (((u_int8_t)strucData->zeroByte & 0x02) == 0x02){
        strucData->upper_x = 0;
    }
    if (((u_int8_t)strucData->zeroByte & 0x01) == 0x01){
        strucData->lower_x = 0;
    }

    x = (u_int16_t) (strucData->upper_x<<8 | strucData->lower_x);
    y = (u_int16_t) (strucData->upper_y<<8 | strucData->lower_y);
    std::stringstream name;
    name<< x ;
    Input* input = mGrid->getInputWithName(name.str().c_str());
    if (input){
        input->setValue(y);
    }

}