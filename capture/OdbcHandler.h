//
//  ODBCHandler.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 13/01/15.
//  Copyright (c) 2015 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__ODBCHandler__
#define __LibLoAndCap__ODBCHandler__

#include "CaptureDevice.h"
#include <soci.h>
#include <soci-odbc.h>
    
#include <stdio.h>
#include <vector>
#include "Grid.h"
#include "ScalingProcessing.h"

class OdbcHandler : public CaptureDevice{
public:
    OdbcHandler(Grid* g, std::string configFile);
    ~OdbcHandler();
    void init();

    void trig();
private:
    soci::session* mSql;
    Grid* mGrid;
    std::vector<std::vector<double>> mRequest;
    std::vector<std::string> mNames;
};
#endif /* defined(__LibLoAndCap__ODBCHandler__) */
