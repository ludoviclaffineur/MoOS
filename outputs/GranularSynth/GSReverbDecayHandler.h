//
//  GSReverbDecayHandler.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 16/12/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__GSReverbDecayHandler__
#define __LibLoAndCap__GSReverbDecayHandler__

#include <stdio.h>
#include "GSParametersHandler.h"
#include "GranularSyntheziser.h"

class GSReverbDecayHandler: public GSParametersHandler{
public:

    GSReverbDecayHandler(GranularSyntheziser* GS);
    bool sendData ();
    void setParameters(std::vector<std::string> ParameterList);
    const float GS_MAX_DECAY = 0.5f;
private:

};


#endif /* defined(__LibLoAndCap__GSReverbDecayHandler__) */
