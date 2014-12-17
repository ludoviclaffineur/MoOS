//
//  GSBlankHandler.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 15/12/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__GSBlankHandler__
#define __LibLoAndCap__GSBlankHandler__

#include <stdio.h>
#include "GSParametersHandler.h"
#include "GranularSyntheziser.h"

class GSBlankHandler: public GSParametersHandler{
public:

    GSBlankHandler(GranularSyntheziser* GS);
    bool sendData ();
    void setParameters(std::vector<std::string> ParameterList);
    const int GS_MAX_BLANK = 10000;
private:

};
#endif /* defined(__LibLoAndCap__GSBlankHandler__) */
