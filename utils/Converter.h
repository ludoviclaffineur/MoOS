//
//  converter.h
//  libpcapTest
//
//  Created by Ludovic Laffineur on 28/10/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#ifndef __libpcapTest__converter__
#define __libpcapTest__converter__

#include <iostream>


class Converter{
public:
    enum TypeOfExtrapolation {
        LINEAR      = 1,
        LOGARITHMIC = 2,
        EXPONENTIAL = 3
    };
    Converter();
    Converter(int typeOfExtrapolation);
    Converter(int typeOfExtrapolation, float xmin, float xmax, float ymin, float ymax);
    float Extrapolate(float inputValue);
    float Linear(float inputValue);
    float Exponential(float inputValue);
    float Logarithmic(float inputValue);
private:
    int _currentExtrapolation;
    float _xMaxValue;
    float _xMinValue;
    float _yMaxValue;
    float _yMinValue;
};
#endif /* defined(__libpcapTest__converter__) */



