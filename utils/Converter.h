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
    void SetDModifier(float d);
    void SetCModifier(float c);
    
private:
    int _currentExtrapolation   = 1;
    float _xMaxValue             = 10;
    float _xMinValue             = 4;
    float _yMaxValue             = 3;
    float _yMinValue             = 1;
    float _cModifier             = 0;
    float _dModifier             = -2;
};
#endif /* defined(__libpcapTest__converter__) */



