//
//  PcapIpProcessing.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 13/03/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__PcapIpProcessing__
#define __LibLoAndCap__PcapIpProcessing__

#include <iostream>
#include "PcapProcessings.h"
#include "Grid.h"

class PcapIpProcessing : public PcapProcessings{
public:
    PcapIpProcessing(Grid* g);
    void setActive(bool active);
    //void process(const u_char* datas);
    void process(const u_char* data);
    //void process();

private:
    Grid* mGrid;
};

#endif /* defined(__LibLoAndCap__PcapIpProcessing__) */
