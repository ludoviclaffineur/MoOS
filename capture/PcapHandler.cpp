//
//  PcapHandler.cpp
//  libpcapTest
//
//  Created by Ludovic Laffineur on 25/10/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#include "PcapHandler.h"
#include <iostream>
PcapHandler::PcapHandler(){
    _filter = NULL;
}

PcapHandler::PcapHandler(char* filter){
    _filter = filter;
}

int PcapHandler::FindAllDevs(pcap_if_t **alldev , char *errbuf){
#ifdef _WIN32
    if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, alldev, errbuf) == -1)
	{
		fprintf(stderr,"Error in pcap_findalldevs: %s\n", errbuf);
		return -1;
	}
#elif defined __APPLE__
    if (pcap_findalldevs(alldev, errbuf)==-1){
        fprintf(stderr, "Couldn't find default device: %s\n", errbuf);
        return -1;
    }
#endif
    return 3;
}

pcap_t* PcapHandler::ListAndChooseInterface(){
    struct bpf_program fcode;
    u_int netmask = 0xffffff00;
    _ListAllDevs();
    pcap_t* handle =  _ChooseDev();
    if (_filter){
        pcap_compile(handle, &fcode, _filter, 1, netmask);
        pcap_setfilter(handle, &fcode);
    }
    return handle;
}

void PcapHandler::_ListAllDevs(){
    pcap_if_t* d;
    FindAllDevs(&_alldevs, _errbuf);
    int i=0;
    for( d = _alldevs; d; d=d->next)
	{
		printf("%d. %s", ++i, d->name);
		if (d->description)
			printf(" (%s)\n", d->description);
		else
			printf(" (No description available)\n");
	}
}

pcap_t* PcapHandler::_ChooseDev(){
    int a;
    pcap_if_t* selected = _alldevs;
    std::cout<< "Select your interface :";
    std::cin >> a;
    for (int i = 1; i<a; i++){
        selected = selected->next;
    }
	return OpenLive(selected->name, BUFSIZ, 1, 1000, _errbuf);
    
}

pcap_t* PcapHandler::OpenLive(const char *device, int snaplen,int promisc, int to_ms, char *errbuf){
    
#ifdef _WIN32
    return pcap_open(device,  // name of the device
                     snaplen,     // portion of the packet to capture.
                     // 65536 grants that the whole packet will be captured on all the MACs.
                     promisc,         // promiscuous mode
                     to_ms,      // read timeout
                     NULL,      // remote authentication
                     errbuf     // error bufferqsdqsdqsd
                     )  ;
    
#elif defined __APPLE__
    return(pcap_open_live(device, snaplen, promisc, to_ms, errbuf));
#endif
}

int PcapHandler::Loop(pcap_t *p, int cnt, pcap_handler callback, u_char *user){
    return pcap_loop(p, cnt, callback, user);
}


void PcapHandler::Close(pcap_t* handle){
    pcap_close(handle);
}

void PcapHandler::FreeAllDevs(pcap_if_t *alldevs){
    pcap_freealldevs(alldevs);
}

