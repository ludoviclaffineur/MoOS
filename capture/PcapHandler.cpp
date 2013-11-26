//
//  PcapHandler.cpp
//  libpcapTest
//
//  Created by Ludovic Laffineur on 25/10/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#include "PcapHandler.h"
#include "IpHeaderDefinitions.h"
#include <pthread.h>

#include <iostream>

pthread_t capture_thread;
bool running = true;

void* ThreadReceptionPacket (void* ptr){
    PcapHandler* p = (PcapHandler*) ptr;
    //pcap_t* handle = (pcap_t*) ptr;
    struct pcap_pkthdr* header;
    const u_char* datas;
    while(running){
        pcap_next_ex(p->getHandle(), &header, &datas);
        std::cout<<header->len<<std::endl;
        ip_header *ih;
        ih = (ip_header *) (datas + 14);
        std::cout<<ih->tlen<<std::endl;
        Grid* g = p->getGrid();
        g->getInputWithName("PacketLength")->setValue(ih->tlen);
        g->compute();
    }
    return NULL;
}

PcapHandler::~PcapHandler(){
    running = false;
    pthread_join(capture_thread, NULL); //waiting that capture_thread finishes
    close(mHandle);
    freeAllDevs(mAlldevs);
}

PcapHandler::PcapHandler(){
    mFilter = NULL;
}

PcapHandler::PcapHandler(char* filter){
    mFilter = filter;
}
PcapHandler::PcapHandler(const char* filter, Grid* g){
    mFilter = filter;
    mGrid = g;
    mGrid->addInput("PacketLength", 1, 65635, -1, 0, Converter::EXPONENTIAL);
}

int PcapHandler::findAllDevs(pcap_if_t **alldev , char *errbuf){
#ifdef _WIN32
    if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, alldev, errbuf) == -1){
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

pcap_t* PcapHandler::listAndChooseInterface(){
    struct bpf_program fcode;
    u_int netmask = 0xffffff00;
    listAllDevs();
    pcap_t* handle =  chooseDev();
    if (mFilter){
        pcap_compile(handle, &fcode, mFilter, 1, netmask);
        pcap_setfilter(handle, &fcode);
    }
    return handle;
}

void PcapHandler::listAllDevs(){
    pcap_if_t* d;
    findAllDevs(&mAlldevs, mErrbuf);
    int i=0;
    for( d = mAlldevs; d; d=d->next){
		printf("%d. %s", ++i, d->name);
		if (d->description)
			printf(" (%s)\n", d->description);
		else
			printf(" (No description available)\n");
	}
}

pcap_t* PcapHandler::chooseDev(){
    int a;
    pcap_if_t* selected = mAlldevs;
    std::cout<< "Select your interface :";
    std::cin >> a;
    for (int i = 1; i<a; i++){
        selected = selected->next;
    }
    mHandle = openLive(selected->name, BUFSIZ, 1, 1000, mErrbuf);
	return mHandle;
}

pcap_t* PcapHandler::getHandle(){
    return mHandle;
}

pcap_t* PcapHandler::openLive(const char *device, int snaplen,int promisc, int to_ms, char *errbuf){
    
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

int PcapHandler::loop(pcap_t *p, int cnt, pcap_handler callback, u_char *user){
    return pcap_loop(p, cnt, callback, user);
}

int PcapHandler::loopThreading(){
    pthread_create(&capture_thread, NULL, ThreadReceptionPacket, this);
    return 0;
}

void PcapHandler::close(pcap_t* handle){
    pcap_close(handle);
}

void PcapHandler::freeAllDevs(pcap_if_t *alldevs){
    pcap_freealldevs(alldevs);
}

Grid* PcapHandler::getGrid(){
    return mGrid;
}
