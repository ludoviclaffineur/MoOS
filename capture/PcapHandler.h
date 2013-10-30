//
//  PcapHandler.h
//  libpcapTest
//
//  Created by Ludovic Laffineur on 25/10/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#ifndef __PcapHandler__
#define __PcapHandler__


#include "pcap.h"

class PcapHandler {
    
public:
    PcapHandler();
    int FindAllDevs(pcap_if_t **alldev, char* errbuff);
    pcap_t* OpenLive(const char *device, int snaplen,int promisc, int to_ms, char *errbuf);
    int Loop(pcap_t *p, int cnt, pcap_handler callback, u_char *user);
    void Close(pcap_t* handle);
    void FreeAllDevs(pcap_if_t *alldevs);
    
private:
    
};
#endif /* defined(__libpcapTest__PcapHandler__) */