//
//  Grid.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 20/11/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#include "Grid.h"

Grid::Grid(){}

void Grid::AddInput(const char* name, float min, float max, float xOffset, float yOffset, int typeOfExtrapolation){
    _Inputs.push_back(new Input(name, min, max, xOffset, yOffset, typeOfExtrapolation));
}

void Grid::AddInput(Input* i){
    _Inputs.push_back(i);
}

void Grid::AddOutput(OutputsHandler* o){
    _Outputs.push_back(o);
}
void Grid::AddCell(const char* inputName, const char* outputName, float corrCoeff){
    _Cells.push_back(new Cell(GetInputWithName(inputName), GetOutputWithName(outputName) , corrCoeff));
}
void Grid::Compute(){
    for (int i = 0; i<_Cells.size(); i++){
        Cell* c = _Cells.at(i);
        c->GetOutput()->AddToValue(c->GetInput()->GetExtrapolatedValue());
    }
    for (int i = 0; i<_Outputs.size(); i++) {
        OutputsHandler* o = _Outputs.at(i);
        o->Extrapolate();
        o->SendData();
        o->Reset();
    }
}

Input* Grid::GetInputWithName(const char* n){
    for(int i =0 ;i<_Inputs.size();i++){
        if (_Inputs.at(i)->CompareName(n)){
            return _Inputs.at(i);
        }

    }
    return NULL;
}

OutputsHandler* Grid::GetOutputWithName(const char* n){
    for(int i =0 ;i<_Inputs.size();i++){
        if (_Outputs.at(i)->CompareName(n)) return _Outputs.at(i);
    }
    return NULL;
}