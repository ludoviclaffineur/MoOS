//
//  Input.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 20/11/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__Input__
#define __LibLoAndCap__Input__

#include <iostream>
#include "Converter.h"

class Input{
public:
    Input();
    Input(const char* name);
    Input(const char* name, Converter c);
    Input(const char* name, float min, float max, int typeOfExtrapolation);
    Input(const char* name, float min, float max, float xOffset, float yOffset, int typeOfExtrapolation);
    ~Input();
    bool CompareName(const char *n);
    void SetValue(float value);
    float GetExtrapolatedValue();

private:
    float _Value;
    char* _Name;
    Converter _Converter;
};

#endif /* defined(__LibLoAndCap__Input__) */
