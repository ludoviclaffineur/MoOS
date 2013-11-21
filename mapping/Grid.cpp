//
//  Grid.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 20/11/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#include "Grid.h"

Grid::Grid(){}

void Grid::AddInput(Input i){
    _Inputs.push_back(i);
}

void Grid::AddOutput(OutputsHandler o){
    _Outputs.push_back(o);
}
void Grid::AddCell(char* inputName, char* outputName, float corrCoeff){
    Input i =_GetInputWithName(inputName);
    OutputsHandler o = _GetOutputWithName(outputName);
    _Cells.push_back(Cell(i, o , corrCoeff));
}
void Compute(){
    //to do
}

Input Grid::_GetInputWithName(char* n){
    for(int i =0 ;i<_Inputs.size();i++){
        if (_Inputs.at(i).CompareName(n)) return _Inputs.at(i);
    }
    return NULL;
}

OutputsHandler Grid::_GetOutputWithName(char* n){
    for(int i =0 ;i<_Inputs.size();i++){
        if (_Outputs.at(i).CompareName(n)) return _Outputs.at(i);
    }
    return OutputsHandler();
}