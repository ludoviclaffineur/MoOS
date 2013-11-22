//
//  OutputsHandler.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 30/10/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#include "OutputsHandler.h"

OutputsHandler::OutputsHandler(){
    _ValueBeforeSending = 0;
}

OutputsHandler::OutputsHandler(const char* n){
    static int i = 0;
    _Name = new char [strlen(n) + 1];
    strcpy(_Name, n);
    i++;
}

bool OutputsHandler::CompareName(const char *n){
    return (strcmp(n, _Name)==0);
}

void OutputsHandler::AddToValue(float a){
    _ValueBeforeSending += a;
}

void OutputsHandler::Extrapolate(){

}

void OutputsHandler::Reset(){
    _ValueBeforeSending = 0;
}

OutputsHandler::~OutputsHandler(){
    delete _Name;
}