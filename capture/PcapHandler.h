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
    ~PcapHandler();
    PcapHandler(char* filter);
    PcapHandler(const char* filter, Grid* g);

    pcap_t* listAndChooseInterface();
    int     findAllDevs(pcap_if_t **alldev, char* errbuff);
    pcap_t* openLive(const char *device, int snaplen,int promisc, int to_ms, char *errbuf);
    int     loop(pcap_t *p, int cnt, pcap_handler callback, u_char *user);
    int     loopThreading();
    void    close(pcap_t* handle);
    void    freeAllDevs(pcap_if_t *alldevs);
    pcap_t* getHandle();
    //pcap_handler _handleFonction;
    Grid*   getGrid();
private:
    void    listAllDevs();
    pcap_t* chooseDev();

    pcap_t*     mHandle;
    char        mErrbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t*  mAlldevs;
    const char* mFilter;
    Grid*       mGrid;
};
#endif /* defined(__libpcapTest__PcapHandler__) */
