//
//  GSDurationHandler.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 15/12/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__GSParametersHandler__
#define __LibLoAndCap__GSParametersHandler__

#include <stdio.h>
#include "OutputsHandler.h"
#include "GranularSyntheziser.h"
class GSParametersHandler: public OutputsHandler{
public:
    GSParametersHandler(const char* n,GranularSyntheziser* GS);
    virtual bool sendData ()=0;
    virtual void setParameters(std::vector<std::string> ParameterList)=0;
protected:
    GranularSyntheziser* mGranularSynth;
};
#endif /* defined(__LibLoAndCap__GSDurationHandler__) */
