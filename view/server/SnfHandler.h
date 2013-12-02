//
//  SnfHandler.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 2/12/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#ifndef HTTP_SNFHANDLER_H
#define HTTP_SNFHANDLER_H

#include <iostream>
#include "Grid.h"
#include "reply.hpp"

namespace http {
namespace server {
    class SnfHandler{
    public:
        SnfHandler(Grid* g);
        bool computeRequest(std::string method, std::string parameters, reply& rep);
    private:
        Grid* mGrid;
    };
}
}

#endif