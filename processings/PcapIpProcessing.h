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
#include <stdarg.h>
#include "PcapProcessings.h"
#include "Grid.h"
#include "Setter.h"


class PcapIpProcessing : public PcapProcessings{
public:
    PcapIpProcessing(Grid* g);
    void setActive(bool active);
    //void process(const u_char* datas);
    void process(const u_char* data);
    //void process();
    void setSetter(Setter<float>* packetLength, Setter<float>* typeOfService, Setter<float>* protocol,Setter<float>* Ttl );

private:
    Grid* mGrid;
    Setter<float>* mTypeOfService;
    Setter<float>* mPacketLength;
    Setter<float>* mProtocol;
    Setter<float>* mTtl;
    void setSetter(int nbrSetters,...);

};

#endif /* defined(__LibLoAndCap__PcapIpProcessing__) */
