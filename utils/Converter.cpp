//
//  converter.cpp
//  libpcapTest
//
//  Created by Ludovic Laffineur on 28/10/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#include "converter.h"
#include <math.h>

Converter::Converter(){}

Converter::Converter(int typeOfExtrapolation){
    _currentExtrapolation = typeOfExtrapolation;
	_xMaxValue = 0;
    _xMinValue = 6;
    _yMaxValue = 0;
    _yMinValue = 1;
}

Converter::Converter(int typeOfExtrapolation, float xmin, float xmax, float ymin, float ymax){
    _currentExtrapolation = typeOfExtrapolation;
    _xMaxValue = xmax;
    _xMinValue = xmin;
    _yMaxValue = ymax;
    _yMinValue = ymin;
}

float Converter::Extrapolate(float inputValue){
    switch (_currentExtrapolation) {
        case LINEAR:
            return Linear(inputValue);
            break;
        case EXPONENTIAL:
            return Exponential(inputValue);
            break;
        case LOGARITHMIC:
            return Logarithmic(inputValue);
            break;
        default:
            return -1;
    }
}

float Converter::Linear(float inputValue){
    float beta = _yMinValue - (_xMinValue*(_yMaxValue-_yMinValue)/(_xMaxValue-_xMinValue));
    float alpha =(_yMaxValue-_yMinValue)/(_xMaxValue-_xMinValue);
    return (alpha*inputValue + beta);
}

float Converter::Exponential(float inputValue){
    float b = log(_yMinValue/_yMaxValue)/(_xMinValue-_xMaxValue);
    float a = _yMinValue/expf(b*_xMinValue);
    return (a*expf(inputValue*b));
}

float Converter::Logarithmic(float inputValue){
    float b = (_yMinValue-_yMaxValue)/log(_xMinValue/_xMaxValue);
    float a = expf(_yMinValue/b)/_xMinValue;
    return ( b*log(a*inputValue));
}