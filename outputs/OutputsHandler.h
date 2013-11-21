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
    virtual bool SendData (int paramNumber, float value){return false;};
    virtual bool SendData (){return false;};
    bool CompareName (const char* n);
    void AddToValue(float a);
    void Reset();
    void Extrapolate();

protected:
    float _ValueBeforeSending;
    int _ParamNumber;
    char* _Name;
    Converter _Converter;
};
#endif /* defined(__LibLoAndCap__OutputsHandler__) */
