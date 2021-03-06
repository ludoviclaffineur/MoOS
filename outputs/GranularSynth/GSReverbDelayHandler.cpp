//
//  GSReverbDelayHandler.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 16/12/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "GSReverbDelayHandler.h"


GSReverbDelayHandler::GSReverbDelayHandler(GranularSyntheziser* GS) : GSParametersHandler("GSReverbDelay",GS){
    //GS_MAX_DURATION = 4000;
    //OutputsHandler::setName("GS_Duration");
}

void GSReverbDelayHandler::setParameters(std::vector<std::string> ParameterList){
    GSParametersHandler::setParameters(ParameterList);
}

bool GSReverbDelayHandler::sendData(){
    mGranularSynth->setDelay((mValueBeforeSending)*GS_MAX_DELAY);
    return true;
}