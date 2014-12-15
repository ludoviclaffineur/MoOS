//
//  GSDurationHandler.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 15/12/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "GSParametersHandler.h"

GSParametersHandler::GSParametersHandler(const char* n,GranularSyntheziser* GS):OutputsHandler(n){
    mGranularSynth = GS;
}