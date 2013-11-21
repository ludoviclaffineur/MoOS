//
//  Cell.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 20/11/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#include "Cell.h"

Cell::Cell(Input i, OutputsHandler o, float coeff){
    _Input = i;
    _Output = o;
    _Coeff = coeff;
}

void Cell:: SetCoeff(float coeff){
    _Coeff = coeff;
}

float Cell::GetCoeff(){
    return _Coeff;
}

Input Cell::GetInput(){
    return _Input;
}
OutputsHandler Cell::GetOutput(){
    return _Output;
}