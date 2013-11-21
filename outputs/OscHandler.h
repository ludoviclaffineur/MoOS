//
//  Osc.h
//  libpcapTest
//
//  Created by Ludovic Laffineur on 29/10/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#ifndef __libpcapTest__OscHandler__
#define __libpcapTest__OscHandler__

#include <iostream>
#include "lo.h"
#include "OutputsHandler.h"

class OscHandler : public OutputsHandler{
public:
    OscHandler();
    OscHandler(const char* n);
    OscHandler(const char* ipAddress, const char* port);
    bool SendData (int paramNumber, float value);
    bool SendData ();
private:
    lo_address _distant;
    
    
};
#endif /* defined(__libpcapTest__Osc__) */
