//
//  PcapLocationProcessing.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 13/03/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__PcapLocationProcessing__
#define __LibLoAndCap__PcapLocationProcessing__

#include <iostream>
#include "PcapProcessings.h"
#include "Grid.h"
#include "LocationIp.h"
#include "CsvImporter.h"

class PcapLocationProcessing : public PcapProcessings{
public:
    PcapLocationProcessing(Grid* g);
    ~PcapLocationProcessing();
    void setActive(bool active);
    //void process(const u_char* datas);
    void process(const u_char* data);
    //void process();
    static float haversine (LocationIp* home, LocationIp* server);

private:
    LocationIp** mIpLocations;
    Grid* mGrid;

    bool isLocalAddress(long int ipadd);
    LocationIp* findLocationFromIpAddress(unsigned long int TargetIp);

    LocationIp* binaryTree(unsigned long int TargetIp);
    LocationIp* secante(unsigned long int TargetIp);
};

#endif /* defined(__LibLoAndCap__PcapLocationProcessing__) */
