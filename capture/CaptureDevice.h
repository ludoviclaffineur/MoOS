//
//  CaptureDevice.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 1/04/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__CaptureDevice__
#define __LibLoAndCap__CaptureDevice__

#include <iostream>


#include "Processings.h"
#include "Grid.h"
#include <vector>
#include <string.h>
class CaptureDevice{
public:


    virtual void init() = 0;
    Grid*   getGrid(){
        return mGrid;
    }
protected:
    std::vector <Processings*> mProcessings;
    Grid*       mGrid;
};

#endif /* defined(__LibLoAndCap__CaptureDevice__) */
