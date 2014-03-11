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
#include "LocationIp.h"
#include "CsvImporter.h"
class PcapHandler {
    
public:
    PcapHandler();
    ~PcapHandler();
    PcapHandler(char* filter);
    PcapHandler(const char* filter, Grid* g);

    void    close(pcap_t* handle);
    void    freeAllDevs(pcap_if_t *alldevs);
    int     findAllDevs(pcap_if_t **alldev, char* errbuff);
    Grid*   getGrid();
    pcap_t* getHandle();
    LocationIp** getIpLocations();
    pcap_t* listAndChooseInterface();
    int     loop(pcap_t *p, int cnt, pcap_handler callback, u_char *user);
    int     loopThreading();
    pcap_t* openLive(const char *device, int snaplen,int promisc, int to_ms, char *errbuf);
    static LocationIp* FindLocationFromIpAddress(unsigned long int TargetIp, PcapHandler* p);
    static void* ThreadReceptionPacket (void* ptr);



private:
    static LocationIp* BinaryTree(unsigned long int TargetIp, PcapHandler* p);
    static LocationIp* Secante(unsigned long int TargetIp, PcapHandler* p);
    pcap_t*     chooseDev();
    void        listAllDevs();

    pcap_if_t*  mAlldevs;
    char        mErrbuf[PCAP_ERRBUF_SIZE];
    const char* mFilter;
    Grid*       mGrid;
    pcap_t*     mHandle;
    LocationIp** mIpLocations;
};

#endif /* defined(__libpcapTest__PcapHandler__) */