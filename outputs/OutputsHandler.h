//
//  OutputsHandler.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 30/10/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__OutputsHandler__
#define __LibLoAndCap__OutputsHandler__

#include <iostream>
#include "Converter.h"
#include <vector>
#include "Parameter.h"

class OutputsHandler{

public:
    OutputsHandler();
    OutputsHandler(const char* n);
    ~OutputsHandler();
    
    void    addToValue(float a);
    bool    compareName (const char* n);
    void    extrapolate();
    const char* getName();
    std::vector<IParameter*>* getParameters();
    void    reset();
    virtual bool sendData (int paramNumber, float value){return false;};
    virtual bool sendData (){return false;};

protected:

    float   mValueBeforeSending;
    int     mParamNumber;
    char*   mName;
    Converter mConverter;
    std::vector<IParameter*> mParameters;
};

#endif /* defined(__LibLoAndCap__OutputsHandler__) */