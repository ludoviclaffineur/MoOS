//
//  GSOverlapHandler.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 15/12/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "GSOverlapHandler.h"

GSOverlapHandler::GSOverlapHandler(GranularSyntheziser* GS) : GSParametersHandler("GSOverlap",GS){
    //GS_MAX_DURATION = 4000;
    //OutputsHandler::setName("GS_Duration");
}

void GSOverlapHandler::setParameters(std::vector<std::string> ParameterList){
    for (int i=0; i<ParameterList.size(); i++) {
        if (ParameterList.at(i).compare("Name")==0) {
            OutputsHandler::setName(ParameterList.at(i+1).c_str());
        }
    }
}

bool GSOverlapHandler::sendData(){
    
    mGranularSynth->setOverlap((mValueBeforeSending)*GS_MAX_OVERLAP);
    return true;
}