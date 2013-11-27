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