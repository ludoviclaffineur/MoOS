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
    void AddInput(Input i);
    void AddInput(const char* Name, float min, float max, float xOffset, float yOffset, int typeOfExtrapolation);
    void AddOutput(OutputsHandler o);
    void AddCell(const char* inputName,const char* outputName, float corrCoeff);
    Input GetInputWithName(const char* n);
    OutputsHandler GetOutputWithName(const char* n);
    void Compute();
private:
    std::vector<Input> _Inputs;
    std::vector<OutputsHandler> _Outputs;
    std::vector<Cell> _Cells;


};
#endif /* defined(__LibLoAndCap__Grid__) */
