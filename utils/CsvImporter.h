//
//  CsvImporter.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 3/03/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__CsvImporter__
#define __LibLoAndCap__CsvImporter__

#include <iostream>
#include "LocationIp.h"
#include <regex>

class CsvImporter{
public:
    static LocationIp** importCsv(std::string &file);
};

#endif /* defined(__LibLoAndCap__CsvImporter__) */
