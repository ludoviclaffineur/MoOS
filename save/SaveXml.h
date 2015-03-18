//
//  SaveXml.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 25/02/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__SaveXml__
#define __LibLoAndCap__SaveXml__

#include <iostream>
#include "Grid.h"
#include "Cell.h"
#include "OutputsHandler.h"
#include "OscHandler.h"
#include "Parameter.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "AppIncludes.h"

class SaveXml{
public:
    static void loadXml(const std::string &filename, Grid* g);
    SaveXml(const std::string &filename,  Grid* g);
    static void createOsc( Grid* g, const boost::property_tree::ptree& pt);
    static std::vector<std::string>* listFiles(std::string path);
};
#endif /* defined(__LibLoAndCap__SaveXml__) */
