//
//  Grid.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 20/11/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#include "Grid.h"

Grid::Grid(){
    mCurrentOutputId = 0;
}

void Grid::addInput(const char* name, float min, float max, float xOffset, float yOffset, int typeOfExtrapolation){
    mInputs.push_back(new Input(name, min, max, xOffset, yOffset, typeOfExtrapolation));
}

void Grid::addInput(Input* i){
    mInputs.push_back(i);
}

void Grid::addOutput(OutputsHandler* o){
    o->setId(mCurrentOutputId++);
    mOutputs.push_back(o);
    addComplementaryCells(o);
}

void Grid::addComplementaryCells(OutputsHandler *o){
    for (int i=0;i< mInputs.size();i++){
        addCell(mInputs.at(i)->getName(), o->getName(), 0.0);
    }
}

void Grid::addCell(const char* inputName, const char* outputName, float corrCoeff){
    mCells.push_back(new Cell(getInputWithName(inputName), getOutputWithName(outputName) , corrCoeff));
}

void Grid::compute(){
    OutputsHandler* oprime = nullptr;
    for (int i = 0; i<mCells.size(); i++){
        Cell* c = mCells.at(i);
        //std::cout<<c->getCoeff()<<std::endl;

        c->getOutput()->addToValue(c->getInput()->getExtrapolatedValue()* c->getCoeff());
        if (oprime ==nullptr){
            oprime = c->getOutput();
        }
    }
    for (int i = 0; i<mOutputs.size(); i++) {
        OutputsHandler* o = mOutputs.at(i);
        o->extrapolate();
        o->sendData();
        o->reset();
    }
}
int Grid::getCurrentOutputId(){
    return mCurrentOutputId;
}

Input* Grid::getInputWithName(const char* n){
    for(int i =0 ;i<mInputs.size();i++)
        if (mInputs.at(i)->compareName(n)) return mInputs.at(i);
    return NULL;
}

OutputsHandler* Grid::getOutputWithName(const char* n){
    for(int i =0 ;i<mOutputs.size();i++)
        if (mOutputs.at(i)->compareName(n)) return mOutputs.at(i);
    return NULL;
}

OutputsHandler* Grid::getOutputWithId(int theId){
    for(int i =0 ;i<mOutputs.size();i++)
        if (theId == mOutputs.at(i)->getId()) return mOutputs.at(i);
    return NULL;
}

size_t Grid::getNbrInputs(){
    return mInputs.size();
}

size_t Grid::getNbrOutputs(){
    return mOutputs.size();
}

std::vector<Input*>* Grid::getInputs(){
    return &mInputs;
}

std::vector<OutputsHandler*>* Grid::getOutputs(){
    return &mOutputs;
}

std::vector<Cell*>* Grid::getCells(){
    return &mCells;
}

Cell* Grid::getCellWithName(std::string input, std::string output){
    for(int i=0;i<mCells.size();i++){
        Cell* c = mCells.at(i);
        if (c->getInput()->getName() == input && c->getOutput()->getName() == output){
            return c;
        }
    }
    return  NULL;
}

void Grid::removeOutput(int id){
    std::vector<Cell*>::iterator i; 
    for (i= mCells.begin(); i!=mCells.end(); ) {
        if ((*i)->getOutput()->getId() == id) {
            i = mCells.erase(i);
        }
        else{
            i++;
        }
    }
    for (int i =0; i<mOutputs.size(); i++) {
        if (mOutputs.at(i)->getId()== id) {
            mOutputs.erase(mOutputs.begin()+i);
            break;
        }
    }

}