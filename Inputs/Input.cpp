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

}

Input::Input(const char* name):_Converter(){
    strcpy(_Name, name);
}

Input::Input(const char* name, Converter c):_Converter(c){
    strcpy(_Name, name);
}

Input::Input(const char* name, float min, float max, int typeOfExtrapolation):_Converter(typeOfExtrapolation, min, max, 0.0, 1.0){
    strcpy(_Name, name);
}

Input::Input(const char* name, float min, float max, float xOffset, float yOffset, int typeOfExtrapolation):
_Converter(typeOfExtrapolation, min, max, 0.0, 1.0,xOffset, yOffset){
    strcpy(_Name, name);
}

bool Input::CompareName(const char *n){
    return strcmp(n, _Name);
}

void Input::setValue(float value){
    _Value = _Converter.Extrapolate(value);
}