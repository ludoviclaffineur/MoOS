//
//  Grid.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 20/11/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#include "Grid.h"

Grid::Grid(){}

void Grid::addInput(const char* name, float min, float max, float xOffset, float yOffset, int typeOfExtrapolation){
    mInputs.push_back(new Input(name, min, max, xOffset, yOffset, typeOfExtrapolation));
}

void Grid::addInput(Input* i){
    mInputs.push_back(i);
}

void Grid::addOutput(OutputsHandler* o){
    mOutputs.push_back(o);
}

void Grid::addCell(const char* inputName, const char* outputName, float corrCoeff){
    mCells.push_back(new Cell(getInputWithName(inputName), getOutputWithName(outputName) , corrCoeff));
}

void Grid::compute(){
    for (int i = 0; i<mCells.size(); i++){
        Cell* c = mCells.at(i);
        c->getOutput()->addToValue(c->getInput()->getExtrapolatedValue());
    }
    for (int i = 0; i<mOutputs.size(); i++) {
        OutputsHandler* o = mOutputs.at(i);
        o->extrapolate();
        o->sendData();
        o->reset();
    }
}

Input* Grid::getInputWithName(const char* n){
    for(int i =0 ;i<mInputs.size();i++)
        if (mInputs.at(i)->compareName(n)) return mInputs.at(i);
    return NULL;
}

OutputsHandler* Grid::getOutputWithName(const char* n){
    for(int i =0 ;i<mInputs.size();i++)
        if (mOutputs.at(i)->compareName(n)) return mOutputs.at(i);
    return NULL;
}

size_t Grid::getNbrInputs(){
    return mInputs.size();
}

std::vector<Input*>* Grid::getInputs(){
    return &mInputs;
}

std::vector<OutputsHandler*>* Grid::getOutputs(){
    return &mOutputs;
}