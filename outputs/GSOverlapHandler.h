//
//  GSOverlapHandler.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 15/12/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__GSOverlapHandler__
#define __LibLoAndCap__GSOverlapHandler__

#include <stdio.h>
#include "GSParametersHandler.h"
#include "GranularSyntheziser.h"

class GSOverlapHandler: public GSParametersHandler{
public:

    GSOverlapHandler(GranularSyntheziser* GS);
    bool sendData ();
    void setParameters(std::vector<std::string> ParameterList);
    const int GS_MAX_OVERLAP = 4000;
private:
    
};

#endif /* defined(__LibLoAndCap__GSOverlapHandler__) */
