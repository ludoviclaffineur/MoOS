//
//  GSReverbDecayHandler.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 16/12/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "GSReverbDecayHandler.h"

GSReverbDecayHandler::GSReverbDecayHandler(GranularSyntheziser* GS) : GSParametersHandler("GSReverbDecay",GS){
    //GS_MAX_DURATION = 4000;
    //OutputsHandler::setName("GS_Duration");
}

void GSReverbDecayHandler::setParameters(std::vector<std::string> ParameterList){
    GSParametersHandler::setParameters(ParameterList);
}

bool GSReverbDecayHandler::sendData(){
    mGranularSynth->setDecay((mValueBeforeSending)*GS_MAX_DECAY);
    return true;
}