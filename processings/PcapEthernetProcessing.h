//
//  PcapEthernetProcessing.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 13/03/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__PcapEthernetProcessing__
#define __LibLoAndCap__PcapEthernetProcessing__

#include <iostream>
#include "Grid.h"
#include "PcapProcessings.h"

class PcapEthernetProcessing : public PcapProcessings{
public:
    PcapEthernetProcessing(Grid* g);
};

#endif /* defined(__LibLoAndCap__PcapEthernetProcessing__) */
