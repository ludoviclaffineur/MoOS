//
//  KymaHandler.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 5/05/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__KymaHandler__
#define __LibLoAndCap__KymaHandler__

#include <iostream>
#include "Grid.h"
#include "lo.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include "OscHandler.h"
class KymaHandler{
public:
    KymaHandler(const char* ipAddress, const char* port, Grid* g);

private:
    lo_server mServerOsc;
    lo_address mAddress;
    Grid* mGrid;
    static int responseFrom(const char *path, const char *types, lo_arg **argv, int argc,void *data, void *user_data);
    static int receivedWidget(const char *path, const char *types, lo_arg **argv, int argc,void *data, void *user_data);
    int widgetId;
};

#endif /* defined(__LibLoAndCap__KymaHandler__) */
