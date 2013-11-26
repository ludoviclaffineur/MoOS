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

class OutputsHandler{
public:
    OutputsHandler();
    OutputsHandler(const char* n);
    ~OutputsHandler();
    virtual bool sendData (int paramNumber, float value){return false;};
    virtual bool sendData (){return false;};
    bool    compareName (const char* n);
    void    addToValue(float a);
    void    reset();
    void    extrapolate();

protected:
    float   mValueBeforeSending;
    int     mParamNumber;
    char*   mName;
    Converter mConverter;
};
#endif /* defined(__LibLoAndCap__OutputsHandler__) */
