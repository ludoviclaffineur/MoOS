//
//  Grid.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 20/11/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__Grid__
#define __LibLoAndCap__Grid__

#include <iostream>
#include "Input.h"
#include "OutputsHandler.h"
#include "Cell.h"
#include <vector>

class Grid{

public:
    Grid();

    void    addInput(Input* i);
    void    addInput(const char* Name, float min, float max, float xOffset, float yOffset, int typeOfExtrapolation);
    void    addOutput(OutputsHandler* o);
    void    addCell(const char* inputName,const char* outputName, float corrCoeff);
    void    compute();
    Input*  getInputWithName(const char* n);
    OutputsHandler* getOutputWithName(const char* n);

private:
    std::vector <Input*> mInputs;
    std::vector <OutputsHandler*> mOutputs;
    std::vector <Cell*>  mCells;
};

#endif /* defined(__LibLoAndCap__Grid__) */