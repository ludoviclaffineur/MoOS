//
//  OutputsHandler.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 30/10/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#include "OutputsHandler.h"

bool OutputsHandler::CompareName(const char *n){
    return strcmp(n, _Name);
}