//
//  Processings.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 13/03/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__Processings__
#define __LibLoAndCap__Processings__

#include <iostream>

class Processings{
public:
    virtual void setActive(bool active) = 0;
    //virtual void process (void* vdata) = 0;
    bool isActive(){return mActive;}
    virtual void setSetter(int nbrSetter,...)=0;

    virtual void process (void* vdata) = 0;
protected:
    bool mActive;
};




#endif /* defined(__LibLoAndCap__Processings__) */
