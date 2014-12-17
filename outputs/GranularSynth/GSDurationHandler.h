//
//  GSDurationHandler.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 15/12/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__GSDurationHandler__
#define __LibLoAndCap__GSDurationHandler__

#include <stdio.h>
#include "GSParametersHandler.h"
#include "GranularSyntheziser.h"

class GSDurationHandler: public GSParametersHandler{
public:

    GSDurationHandler(GranularSyntheziser* GS);
    bool sendData ();
    void setParameters(std::vector<std::string> ParameterList);
    const int GS_MAX_DURATION = 4000;
private:

};
#endif /* defined(__LibLoAndCap__GSDurationHandler__) */
