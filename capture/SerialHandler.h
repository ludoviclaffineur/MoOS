//
//  SerialHandler.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 21/03/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__SerialHandler__
#define __LibLoAndCap__SerialHandler__

#include <iostream>
#include <boost/asio/serial_port.hpp>
#include <boost/asio.hpp>
#include "Grid.h"

class SerialHandler{
public:
    SerialHandler(Grid* g);
    char readChar();
    std::string readResponse();
private:
    Grid* mGrid;
};

#endif /* defined(__LibLoAndCap__SerialHandler__) */
