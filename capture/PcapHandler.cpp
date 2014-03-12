//
//  PcapHandler.cpp
//  libpcapTest
//
//  Created by Ludovic Laffineur on 25/10/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#include "PcapHandler.h"

#include <pthread.h>
#include <iostream>



pthread_t capture_thread;
bool running = true;



void* PcapHandler::ThreadReceptionPacket (void* ptr){
    PcapHandler* p = (PcapHandler*) ptr;
    pthread_setname_np("ThreadPcap");
    //pcap_t* handle = (pcap_t*) ptr;
    struct pcap_pkthdr* header;
    const u_char* datas;
    int res;
    while(running){
        res = pcap_next_ex(p->getHandle(), &header, &datas);
        if (res >0 && datas){
            ip_header *ih;
            Grid* g = p->getGrid();
            ih = (ip_header *) (datas + 14);
            //std::cout<<ih->tlen<<std::endl;

            g->getInputWithName("PacketLength")->setValue(ih->tlen);
            //std::cout<< "Ip dest :" << <<std::endl;
            PcapHandler::setLocalisation(p, ih);
            g->compute();
        }
    }
    return NULL;
}

void PcapHandler::setLocalisation(PcapHandler* p, ip_header* ih){
    Grid* g = p->getGrid();
    long int ipadd =ntohl(ih->saddr.int_address);
    if(PcapHandler::isLocalAddress(ipadd)){
        g->getInputWithName("SourceLatitude")->setValue(51);
        g->getInputWithName("SourceLongitude")->setValue(4);
        ipadd = ntohl(ih->daddr.int_address);
        if( PcapHandler::isLocalAddress(ipadd) ){
            g->getInputWithName("DestLatitude")->setValue(51);
            g->getInputWithName("DestLongitude")->setValue(4);
        }
        else{
            LocationIp* l = PcapHandler::FindLocationFromIpAddress(ntohl(ih->daddr.int_address),p);
            if(l){
                g->getInputWithName("DestLatitude")->setValue(l->getLatitude());
                g->getInputWithName("DestLongitude")->setValue(l->getLongitude());
            }
        }
        //std::cout<< "LOCAL NETWORK"<< std::endl;
    }
    else{
        LocationIp* l = PcapHandler::FindLocationFromIpAddress(ntohl(ih->saddr.int_address),p);
        if(l){
            g->getInputWithName("SourceLatitude")->setValue(l->getLatitude());
            g->getInputWithName("SourceLongitude")->setValue(l->getLongitude());
            g->getInputWithName("DestLatitude")->setValue(51);
            g->getInputWithName("DestLongitude")->setValue(4);
            //std::cout<< "EXTERNAL NETWORK"<< std::endl;
        }
    }
}

bool PcapHandler::isLocalAddress(long int ipadd){
    return (ipadd > TEN_ZERO_ZERO_ZERO && ipadd <= TEN_FIFTY_TWO) || (ipadd > ONE_SEVENTY_TWO_MIN && ipadd <= ONE_SEVENTY_TWO_MAX) || (ipadd > ONE_NINETY_TWO_MIN && ipadd <= ONE_NINETY_TWO_MAX);
}

PcapHandler::~PcapHandler(){
    running = false;

    pthread_join(capture_thread, NULL); //waiting that capture_thread finishes
    close(mHandle);
    freeAllDevs(mAlldevs);
    for (int i = 0; i<NBR_IP_ADDRESSES; i++) {
        delete mIpLocations[i];
    }
    delete [] mIpLocations;
}

PcapHandler::PcapHandler(){
    mFilter = NULL;
}

LocationIp** PcapHandler::getIpLocations(){
    return mIpLocations;
}

LocationIp* PcapHandler::FindLocationFromIpAddress(unsigned long int TargetIp, PcapHandler* p){
    return PcapHandler::BinaryTree(TargetIp,p);
    //return PcapHandler::Secante(TargetIp, p);
}

LocationIp* PcapHandler::BinaryTree(unsigned long int TargetIp, PcapHandler* p){
    LocationIp** ipLoc = p->getIpLocations();
    int min = 0, max = NBR_IP_ADDRESSES-1;
    int middle;
    int i;
    for( i = 0; i<30; i++){
        middle = (max+min)/2;
        if (TargetIp >= ipLoc[middle]->getIpBegin() && TargetIp < ipLoc[middle+1]->getIpBegin()) {
            //std::cout<<"Nbr iterations = " << i <<std::endl;
            return ipLoc[middle];
        }
        else{
            if (TargetIp >= ipLoc[middle]->getIpBegin() && TargetIp <= ipLoc[max]->getIpBegin()) {
                min = middle;
            }
            else{
                max= middle;
            }
        }
    }

    return NULL;
}

LocationIp* PcapHandler::Secante(unsigned long int TargetIp, PcapHandler* p){
    int x_2;
    int x_1 = 0;
    int x_0 = NBR_IP_ADDRESSES-1;
    LocationIp** ipLoc = p->getIpLocations();
    for (int i=0;i<30;i++){
        x_2 = (float)x_1 - ((float)(x_1-x_0)/(float)(ipLoc[x_1]->getIpBegin()-ipLoc[x_0]->getIpBegin()))*(float)(ipLoc[x_1]->getIpBegin()-TargetIp);

        if(ipLoc[x_2]->getIpBegin() <=TargetIp &&ipLoc[x_2+1]->getIpBegin() > TargetIp){
            std::cout<< "range trouvé  "<<ipLoc[x_2]->getIpBegin() << "--"<< ipLoc[x_2+1]->getIpBegin() <<std::endl;
            std::cout<< "Target  "<<TargetIp <<std::endl;
            std::cout<< "Nbr iteration  " << i <<std::endl ;
            return ipLoc[x_2];
        }
        else{
            x_0 = x_1;
            x_1 = x_2;
        }
    }
    return NULL;
}

PcapHandler::PcapHandler(char* filter){
    mFilter = filter;
}

PcapHandler::PcapHandler(const char* filter, Grid* g){
    mFilter = filter;
    mGrid = g;
    std::string csvstring ="IpGps.csv";
    mIpLocations = CsvImporter::importCsv(csvstring);
    mGrid->addInput("PacketLength", 1, 65535, -1, 0, Converter::LINEAR);
    mGrid->addInput("SourceLatitude", 90, -90, -1, 0, Converter::LINEAR);
    mGrid->addInput("SourceLongitude", -180, 180, -1, 0, Converter::LINEAR);
    mGrid->addInput("DestLatitude", 90, -90, -1, 0, Converter::LINEAR);
    mGrid->addInput("DestLongitude", -180, 180, -1, 0, Converter::LINEAR);

    //mGrid->addInput("Protocol", 1, 65635, -20, -100000, Converter::LOGARITHMIC);
    //mGrid->addInput("Port Number", 1, 65635, -1, 0, Converter::EXPONENTIAL);
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

