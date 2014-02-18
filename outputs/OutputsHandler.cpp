//
//  OutputsHandler.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 30/10/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#include "OutputsHandler.h"

OutputsHandler::OutputsHandler(){
    mValueBeforeSending = 0;
}

OutputsHandler::OutputsHandler(const char* n){
    mName = new char [strlen(n) + 1];
    strcpy(mName, n);
    mParameters.push_back(new Parameter<char**>("Name", &mName));
    mParameters.push_back(new Parameter<int*>("Identifier", &mId));
}

bool OutputsHandler::compareName(const char *n){
    return (strcmp(n, mName)==0);
}

void OutputsHandler::addToValue(float a){
    mValueBeforeSending += a;
}

void OutputsHandler::extrapolate(){

}

void OutputsHandler::reset(){
    mValueBeforeSending = 0;
}

OutputsHandler::~OutputsHandler(){
    delete mName;
}


const char* OutputsHandler::getName(){
    return mName;
}

void OutputsHandler::setName(const char *n){
    if (mName) {
        delete mName;
    }
    mName = new char [strlen(n) + 1];
    strcpy(mName, n);
}

int OutputsHandler::getId(){
    return mId;
}

void OutputsHandler::setId(int newId){
    mId = newId;
}
std::vector<IParameter*>* OutputsHandler::getParameters(){
    return &mParameters;
}