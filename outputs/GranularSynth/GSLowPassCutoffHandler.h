//
//  GSLowPassCutoffHandler.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 16/12/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__GSLowPassCutoffHandler__
#define __LibLoAndCap__GSLowPassCutoffHandler__

#include <stdio.h>
#include "GSParametersHandler.h"
#include "GranularSyntheziser.h"
class GSLowPassCutoffHandler: public GSParametersHandler{
public:
    GSLowPassCutoffHandler(GranularSyntheziser* GS);
    bool sendData ();
    void setParameters(std::vector<std::string> ParameterList);
    const int GS_MAX_Cutoff = 20000;
private:

};
#endif /* defined(__LibLoAndCap__GSLowPassCutoffHandler__) */
