//
//  Cell.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 20/11/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#include "Cell.h"

Cell::Cell(Input* i, OutputsHandler* o, float coeff){
    mInput =i;
    mOutput = o;
    mCoeff = coeff;
}

void Cell:: setCoeff(float coeff){
    mCoeff = coeff;
}

float Cell::getCoeff(){
    return mCoeff;
}

Input* Cell::getInput(){
    return mInput;
}

OutputsHandler* Cell::getOutput(){
    return mOutput;
}