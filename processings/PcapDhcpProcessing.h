//
//  PcapDhcpProcessing.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 12/05/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__PcapDhcpProcessing__
#define __LibLoAndCap__PcapDhcpProcessing__

#include <iostream>
#include "PcapProcessings.h"
#include "Grid.h"
class PcapDhcpProcessing : public PcapProcessings{
public:
    PcapDhcpProcessing(Grid* g);
    void process (const u_char* data);
    void setActive (bool active);
private:
    Grid* mGrid;
    Input* mInput;
};


#endif /* defined(__LibLoAndCap__PcapDhcpProcessing__) */
