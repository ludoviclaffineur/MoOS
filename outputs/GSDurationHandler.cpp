//
//  GSDurationHandler.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 15/12/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "GSDurationHandler.h"

GSDurationHandler::GSDurationHandler(GranularSyntheziser* GS) : GSParametersHandler("GSDuration",GS){
    //GS_MAX_DURATION = 4000;
    //OutputsHandler::setName("GS_Duration");
}

void GSDurationHandler::setParameters(std::vector<std::string> ParameterList){
    for (int i=0; i<ParameterList.size(); i++) {
        if (ParameterList.at(i).compare("Name")==0) {
            OutputsHandler::setName(ParameterList.at(i+1).c_str());
        }
    }
}

bool GSDurationHandler::sendData(){
    std::cout<<mValueBeforeSending<<std::endl;
    mGranularSynth->setDuration(mValueBeforeSending*GS_MAX_DURATION);
    return true;
}