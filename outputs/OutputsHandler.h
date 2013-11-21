//
//  OutputsHandler.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 30/10/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__OutputsHandler__
#define __LibLoAndCap__OutputsHandler__

#include <iostream>
class OutputsHandler{
public:
    virtual bool SendData (int paramNumber, float value){return false;};
    bool CompareName (const char* n);
protected:
    char* _Name;
};
#endif /* defined(__LibLoAndCap__OutputsHandler__) */
