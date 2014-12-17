//
//  GSReverbDelayHandler.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 16/12/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__GSReverbDelayHandler__
#define __LibLoAndCap__GSReverbDelayHandler__

#include <stdio.h>
#include "GSParametersHandler.h"
#include "GranularSyntheziser.h"

class GSReverbDelayHandler: public GSParametersHandler{
public:
    GSReverbDelayHandler(GranularSyntheziser* GS);
    bool sendData ();
    void setParameters(std::vector<std::string> ParameterList);
    const float GS_MAX_DELAY = 200;
private:
    
};


#endif /* defined(__LibLoAndCap__GSReverbDelayHandler__) */
