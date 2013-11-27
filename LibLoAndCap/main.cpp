//
//  main.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 30/10/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#include "AppIncludes.h"
#include "server.hpp"
#include <pthread.h>

Grid* TheGrid;
const char* filter ="ip and dst host 172.30.8.13";

int main(int argc, const char * argv[])
{
    TheGrid = new Grid();
    PcapHandler _pcap = PcapHandler(filter, TheGrid);
    const char* osc1= "OSC1";
    OscHandler oscSender= OscHandler(osc1);
    TheGrid->addOutput(&oscSender);
    TheGrid->addCell("PacketLength", "OSC1", 1.0);
	_pcap.listAndChooseInterface();
    _pcap.loopThreading();
    
    // Control board

    http::server::server s("0.0.0.0", "80", "./www");
    s.run();

    std::cout<<"YOUPS";
    int a;
    std::cin>>a;
    return 0;
}