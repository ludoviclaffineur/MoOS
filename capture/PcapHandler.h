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
#include "Grid.h"
#include "Input.h"
class PcapHandler {
    
public:
    PcapHandler();
    PcapHandler(char* filter);
    PcapHandler(char* filter, Grid* g);
    pcap_t* ListAndChooseInterface();
    int FindAllDevs(pcap_if_t **alldev, char* errbuff);
    pcap_t* OpenLive(const char *device, int snaplen,int promisc, int to_ms, char *errbuf);
    int Loop(pcap_t *p, int cnt, pcap_handler callback, u_char *user);
    void Close(pcap_t* handle);
    void FreeAllDevs(pcap_if_t *alldevs);
    
private:
    void _ListAllDevs();
    pcap_t* _ChooseDev();
    
    char _errbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t* _alldevs;
    char* _filter;
    Grid _TheGrid;
};
#endif /* defined(__libpcapTest__PcapHandler__) */
