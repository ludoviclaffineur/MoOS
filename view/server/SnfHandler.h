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
#include "string.h"

namespace http {
namespace server {
    //enum class MONTEST { A,S,C,Q};
    class SnfHandler{

    public:
        SnfHandler(Grid* g);
        bool computeRequest(std::string method, std::string parameters, reply& rep);
        std::vector <std::string> ExtractPamameters(std::string rawParameters);

    private:
        int findIdInListParameters(std::vector<std::string> listParam);
        int findTypeInListParameters(std::vector<std::string> listParam);
        Grid* mGrid;
    };
}
}

#endif
