//
//  GSInitPositionHandler.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 16/12/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__GSInitPositionHandler__
#define __LibLoAndCap__GSInitPositionHandler__

#include <stdio.h>
#include "GSParametersHandler.h"
#include "GranularSyntheziser.h"

class GSInitPositionHandler: public GSParametersHandler{
public:
    GSInitPositionHandler(GranularSyntheziser* GS);
    bool sendData ();
    void setParameters(std::vector<std::string> ParameterList);
    int GS_MAX_POSITION;
private:

};
#endif /* defined(__LibLoAndCap__GSInitPositionHandler__) */
