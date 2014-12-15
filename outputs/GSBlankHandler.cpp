//
//  GSBlankHandler.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 15/12/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "GSBlankHandler.h"


GSBlankHandler::GSBlankHandler(GranularSyntheziser* GS) : GSParametersHandler("GSBlank",GS){
    //GS_MAX_DURATION = 4000;
    //OutputsHandler::setName("GS_Duration");
}

void GSBlankHandler::setParameters(std::vector<std::string> ParameterList){
    for (int i=0; i<ParameterList.size(); i++) {
        if (ParameterList.at(i).compare("Name")==0) {
            OutputsHandler::setName(ParameterList.at(i+1).c_str());
        }
    }
}

bool GSBlankHandler::sendData(){

    mGranularSynth->setBlank((1-mValueBeforeSending)*GS_MAX_BLANK);
    return true;
}