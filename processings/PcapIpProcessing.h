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

//* Gather infomation from IP packet
class PcapIpProcessing : public PcapProcessings{
public:
    //! Constructor
    PcapIpProcessing(Grid* g);
    void setActive(bool active);
    void process(const u_char* data);
    //! Set output setters
    void setSetter(Setter<float>* packetLength, Setter<float>* typeOfService, Setter<float>* protocol,Setter<float>* Ttl );

private:
    Grid* mGrid;
    //! Output setter TypeOfService
    Setter<float>* mTypeOfService;
    //! Output setter Protocol
    Setter<float>* mPacketLength;
    //! Output setter Protocol
    Setter<float>* mProtocol;
    //! Output setter TTL
    Setter<float>* mTtl;

    void setSetter(int nbrSetters,...);

};

#endif /* defined(__LibLoAndCap__PcapIpProcessing__) */
