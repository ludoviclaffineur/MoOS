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
    void AddOutput(OutputsHandler o);
    void AddCell(char* inputName, char* outputName, float corrCoeff);
    void Compute();
private:
    std::vector<Input> _Inputs;
    std::vector<OutputsHandler> _Outputs;
    std::vector<Cell> _Cells;

    Input _GetInputWithName(char* n);
    OutputsHandler _GetOutputWithName(char* n);
};
#endif /* defined(__LibLoAndCap__Grid__) */
