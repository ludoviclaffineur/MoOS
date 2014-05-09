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
    enum OutputType{
        OSC,
        Total
    };
    OutputsHandler();
    OutputsHandler(const char* n);
    OutputsHandler(const char* n, float min, float max);
    ~OutputsHandler();
    void    setId(int newId);
    int     getId();
    void    addToValue(float a);
    bool    compareName (const char* n);
    void    extrapolate();
    const char* getName();
    int     getOuputType();
    void setName(const char* n);
    std::vector<IParameter*>* getParameters();
    void    reset();
    virtual bool sendData (int paramNumber, float value){return false;};
    virtual bool sendData (){return false;};
    virtual void setParameters(std::vector<std::string> ParameterList)=0;
protected:

    int     mId;
    int     mOutputType;
    float   mValueBeforeSending;
    int     mParamNumber; //pas topitop
    char*   mName;
    Converter mConverter;
    std::vector<IParameter*> mParameters;
};

#endif /* defined(__LibLoAndCap__OutputsHandler__) */