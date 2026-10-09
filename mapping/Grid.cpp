//
//  Grid.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 20/11/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#include "Grid.h"
#include <ctime>

Grid::Grid(){
    mCurrentOutputId = 0;
    mActive=false;
    //mWebSocket = new WebSocketServer(9002);
    //mWebSocket->start();
    mIsMonitored = true;
}

Grid::~Grid(){
    for(int i = 0; i<mInputs.size();i++){
        delete mInputs[i];
    }
    for(int i = 0; i<mOutputs.size();i++){
        delete mOutputs[i];
    }
    for(int i = 0; i<mCells.size();i++){
        delete mCells[i];
    }
    //delete mWebSocket;
}

float* Grid::getCoeffs(){
    std::lock_guard<std::recursive_mutex> lock(mMutex);

    float* coeffs = new float[mCells.size()];
    std::vector<Cell*>::iterator i;
    int j=0;
    for (i= mCells.begin(); i!=mCells.end();i++,j++ ) {
        coeffs[j] = (*i)->getCoeff();
    }
    return coeffs;
}

void Grid::setCoeffs(float *coeffs){
    std::lock_guard<std::recursive_mutex> lock(mMutex);

    std::vector<Cell*>::iterator i;
    int j=0;
    for (i= mCells.begin(); i!=mCells.end();i++,j++ ) {
        (*i)->setCoeff(((int)(coeffs[j]*100))/100.0f);
    }

}

void Grid::setCoeffs(float **coeffs){
    std::lock_guard<std::recursive_mutex> lock(mMutex);

    std::vector<Cell*>::iterator i;
    int j=0;
    for (i= mCells.begin(); i!=mCells.end();i++,j++ ) {
        (*i)->setCoeff(coeffs[j%getNbrInputs()][j/getNbrInputs()]);
    }

}


void Grid::addInput(const char* name, float min, float max, float xOffset, float yOffset, int typeOfExtrapolation){
    std::lock_guard<std::recursive_mutex> lock(mMutex);

    mInputs.push_back(new Input(name, min, max, xOffset, yOffset, typeOfExtrapolation));
}

void Grid::addInput(Input* i){
    std::lock_guard<std::recursive_mutex> lock(mMutex);

    mInputs.push_back(i);
}

void Grid::addOutput(OutputsHandler* o){
    std::lock_guard<std::recursive_mutex> lock(mMutex);

    o->setId(mCurrentOutputId++);
    mOutputs.push_back(o);
    addComplementaryCells(o);
}

void Grid::addComplementaryCells(OutputsHandler *o){
    std::lock_guard<std::recursive_mutex> lock(mMutex);

    for (int i=0;i< mInputs.size();i++){
        addCell(mInputs.at(i)->getName(), o->getName(), 0.0);
    }
}

void Grid::addCell(const char* inputName, const char* outputName, float corrCoeff){
    std::lock_guard<std::recursive_mutex> lock(mMutex);

    mCells.push_back(new Cell(getInputWithName(inputName), getOutputWithName(outputName) , corrCoeff));
}

void Grid::compute(){
    std::lock_guard<std::recursive_mutex> lock(mMutex);

    if (mIsMonitored){
        //mWebSocket->sendMessage(getInputs());
    }
    if (mActive) {
        std::vector<Cell*>::iterator i;
        for (i= mCells.begin(); i!=mCells.end();i++ ) {
            (*i)->getOutput()->addToValue((*i)->getInput()->getExtrapolatedValue()* (*i)->getCoeff());
        }
        std::vector<OutputsHandler*>::iterator j;
        for (j= mOutputs.begin(); j!=mOutputs.end();j++ ) {
            (*j)->extrapolate();
            (*j)->sendData(); //COST A MAX
            (*j)->reset();
        }
    }
}
int Grid::getCurrentOutputId(){
    return mCurrentOutputId;
}

Input* Grid::getInputWithName(const char* n){
    std::lock_guard<std::recursive_mutex> lock(mMutex);

    std::vector<Input*>::iterator j;
    for (j= mInputs.begin(); j!=mInputs.end();j++ ) {
        if ((*j)->compareName(n)) return (*j);
    }
    return NULL;
}

OutputsHandler* Grid::getOutputWithName(const char* n){
    std::lock_guard<std::recursive_mutex> lock(mMutex);

    std::vector<OutputsHandler*>::iterator j;
    for (j= mOutputs.begin(); j!=mOutputs.end();j++ ) {
        if ((*j)->compareName(n)) return (*j);
    }
    return NULL;
}

OutputsHandler* Grid::getOutputWithId(int theId){
    std::lock_guard<std::recursive_mutex> lock(mMutex);

    std::vector<OutputsHandler*>::iterator j;
    for (j= mOutputs.begin(); j!=mOutputs.end();j++ ) 
        if (theId == (*j)->getId()) return (*j);
    return NULL;
}

size_t Grid::getNbrInputs(){
    std::lock_guard<std::recursive_mutex> lock(mMutex);

    return mInputs.size();
}

size_t Grid::getNbrOutputs(){
    std::lock_guard<std::recursive_mutex> lock(mMutex);

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
    std::lock_guard<std::recursive_mutex> lock(mMutex);

    for(int i=0;i<mCells.size();i++){
        Cell* c = mCells.at(i);
        if (c->getInput()->getName() == input && c->getOutput()->getName() == output){
            return c;
        }
    }
    return  NULL;
}

void Grid::removeOutput(int id){
    std::lock_guard<std::recursive_mutex> lock(mMutex);

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


