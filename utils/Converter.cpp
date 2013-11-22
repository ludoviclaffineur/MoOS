//
//  converter.cpp
//  libpcapTest
//
//  Created by Ludovic Laffineur on 28/10/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#include "Converter.h"
#include <math.h>

Converter::Converter(){}

Converter::Converter(int typeOfExtrapolation){
    _currentExtrapolation = typeOfExtrapolation;
	_xMaxValue = 0;
    _xMinValue = 6;
    _yMaxValue = 0;
    _yMinValue = 1;
	_yOffset = -3;
	_xOffset = -1;
}

Converter::Converter(Converter * c){
    memcpy(this, c, sizeof(Converter));
}

Converter::Converter(int typeOfExtrapolation, float xmin, float xmax, float ymin, float ymax){
    _currentExtrapolation = typeOfExtrapolation;
    _xMaxValue = xmax;
    _xMinValue = xmin;
    _yMaxValue = ymax;
    _yMinValue = ymin;
    _yOffset = 0;
	_xOffset = 0;
}

Converter::Converter(int typeOfExtrapolation, float xmin, float xmax, float ymin, float ymax, float xOffset, float yOffset){
    _currentExtrapolation = typeOfExtrapolation;
    _xMaxValue = xmax;
    _xMinValue = xmin;
    _yMaxValue = ymax;
    _yMinValue = ymin;
    _yOffset = yOffset;
	_xOffset = xOffset;
}

float Converter::Extrapolate(float inputValue){
    switch (_currentExtrapolation) {
        case LINEAR:
            return _Linear(inputValue);
            break;
        case EXPONENTIAL:
            return _Exponential(inputValue);
            break;
        case LOGARITHMIC:
            return _Logarithmic(inputValue);
            break;
        default:
            return -1;
    }
}

float Converter::_Linear(float inputValue){
    float beta = _yMinValue - (_xMinValue*(_yMaxValue-_yMinValue)/(_xMaxValue-_xMinValue));
    float alpha =(_yMaxValue-_yMinValue)/(_xMaxValue-_xMinValue);
    return (alpha*inputValue + beta);
}

float Converter::_Exponential(float inputValue){
    float b = log((_yMinValue-_xOffset)/(_yMaxValue-_xOffset))/(_xMinValue-_xMaxValue);
    float a = (_yMinValue-_xOffset)/expf(b*_xMinValue-_yOffset);
    //std::cout<<a<<" " << b<< std::endl;
    return (a*expf((inputValue-_yOffset)*b)+_xOffset);
}

float Converter::_Logarithmic(float inputValue){
    float b = (_yMinValue-_yMaxValue)/log((_xMinValue-_yOffset)/(_xMaxValue-_yOffset));
    float a = expf((_yMinValue-_xOffset)/b)/(_xMinValue-_yOffset);
    //std::cout<<a<<" " << b<< std::endl;
    return ( b*log(a*(inputValue-_yOffset))+_xOffset);
}

void Converter::SetDModifier(float d){
    _xOffset = d;
}

void Converter::SetCModifier(float c){
    _yOffset = c;
}