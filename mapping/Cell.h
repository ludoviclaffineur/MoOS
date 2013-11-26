//
//  Cell.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 20/11/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__Cell__
#define __LibLoAndCap__Cell__

#include <iostream>
#include "Input.h"
#include "OutputsHandler.h"

class Cell{

public:
    Cell(Input* i, OutputsHandler* o, float coeff);

    void            setCoeff(float coeff);
    float           getCoeff();
    Input*          getInput();
    OutputsHandler* getOutput();

private:
    float           mCoeff;
    Input*          mInput;
    OutputsHandler* mOutput;
};

#endif /* defined(__LibLoAndCap__Cell__) */