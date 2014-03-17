//
//  PcapProcessings.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 13/03/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__PcapProcessings__
#define __LibLoAndCap__PcapProcessings__

#include <iostream>
#include "Processings.h"

class PcapProcessings : public Processings {
public:
    PcapProcessings(){};
    virtual void setActive(bool active) = 0;
    //virtual void process(const u_char* datas) = 0;
    virtual void process (const u_char* data) =0;
    void process(void* vdata){
        process (*((const u_char**) vdata));
    };

    //virtual void process();
};

#endif /* defined(__LibLoAndCap__PcapProcessings__) */
