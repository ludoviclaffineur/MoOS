//
//  Input.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 20/11/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#include "Input.h"
#include <string.h>

Input::Input(){
    _Name = new char [1];
}

Input::Input(const char* name):_Converter(){
    _Name = new char [strlen(name)+1];
    strcpy(_Name, name);
}

Input::Input(const char* name, Converter c):_Converter(c){
    _Name = new char [strlen(name)+1];
    strcpy(_Name, name);
}

Input::Input(const char* name, float min, float max, int typeOfExtrapolation):
_Converter(typeOfExtrapolation, min, max, 0.0, 1.0) {
    _Name = new char [strlen(name)+1];
    strcpy(_Name, name);
}

Input::Input(const char* name, float min, float max, float xOffset, float yOffset, int typeOfExtrapolation):
_Converter(typeOfExtrapolation, min, max, 0.0, 1.0,xOffset, yOffset){
    _Name = new char [strlen(name)+1];
    strcpy(_Name, name);
}

bool Input::CompareName(const char *n){
    //printf("NameInput : %s \n Name to test : %s \n Result strcmp : %d", _Name, n,strcmp(n, _Name));
    bool a = (strcmp(n, _Name)==0);
    return a;
}

void Input::SetValue(float value){
    _Value = _Converter.Extrapolate(value);
    //std::cout<<"Converted Value"<< _Value<< std::endl;
}

float Input::GetExtrapolatedValue(){
    return _Value;
}

Input::~Input(){
    delete _Name;
}