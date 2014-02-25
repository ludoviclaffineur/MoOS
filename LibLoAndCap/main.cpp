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
    pthread_setname_np("Main");
    TheGrid = new Grid();
    PcapHandler _pcap = PcapHandler(filter, TheGrid);
    const char* osc1= "OSC1";


    TheGrid->addOutput(new OscHandler(osc1,"127.0.0.1","20000", "/osc", "f" ));
    //TheGrid->addOutput(new OscHandler(osc2,"192.168.1.1","20001", "/osc", "f" ));
    //TheGrid->addOutput(new OscHandler(osc3));

    /*TheGrid->addCell("PacketLength", "OSC1", 1.0);
    TheGrid->addCell("PacketLength", "OSC2", 0.9);


    TheGrid->addCell("TTL", "OSC1", 0.7);
    TheGrid->addCell("TTL", "OSC2", 0.6);


    TheGrid->addCell("Distance", "OSC1", 0.4);
    TheGrid->addCell("Distance", "OSC2", 0.3);*/


	_pcap.listAndChooseInterface();
    _pcap.loopThreading();
    
    // Control board
    std::cout<<"Lauching Web server http://127.0.0.1"<<std::endl;
    
    http::server::server s("0.0.0.0", "80", "./www", TheGrid);
    s.run();

    std::cout<<"Shuting down Web server..."<<std::endl;
 //   int a;
  //  std::cin>>a;
    return 0;
}