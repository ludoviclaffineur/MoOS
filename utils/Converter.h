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
    Converter(Converter * c);
    Converter(int typeOfExtrapolation);
    Converter(int typeOfExtrapolation, float xmin, float xmax, float ymin, float ymax);
    Converter(int typeOfExtrapolation, float xmin, float xmax, float ymin, float ymax, float xOffset, float yOffset);
    float Extrapolate(float inputValue);
    void SetDModifier(float d);
    void SetCModifier(float c);
    
private:
    int _currentExtrapolation;
    float _Linear(float inputValue);
    float _Exponential(float inputValue);
    float _Logarithmic(float inputValue);
    float _xMaxValue;
    float _xMinValue;
    float _yMaxValue;
    float _yMinValue;
    float _xOffset;
    float _yOffset;
};
#endif /* defined(__libpcapTest__converter__) */



