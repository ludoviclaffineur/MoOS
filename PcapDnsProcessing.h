//
//  PcapDnsProcessing.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 24/04/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__PcapDnsProcessing__
#define __LibLoAndCap__PcapDnsProcessing__
#include "PcapProcessings.h"
#include "IpHeaderDefinitions.h"
#include <iostream>
#include <string.h>
#include <regex>
#include <sstream>
#include "OscHandler.h"

class PcapDnsProcessing : public PcapProcessings{
public:
    PcapDnsProcessing();
    void process(const u_char* data);
    void setActive (bool active);
    const char* rleDecompress(const u_char* payload);
private:
    bool isDnsRequest(ip_header ih, udp_header uh);
    OscHandler* OscOutputParent;
    OscHandler* OscOutputChild;
};
#endif /* defined(__LibLoAndCap__PcapDnsProcessing__) */
