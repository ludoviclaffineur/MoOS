//
//  PcapDnsProcessing.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 24/04/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "PcapDnsProcessing.h"


PcapDnsProcessing::PcapDnsProcessing(){

}

void PcapDnsProcessing::process(const u_char *data){
    ip_header *ih;
    ih = (ip_header *) (data + 14);
    if (ih->proto == 17){
        udp_header* uh = (udp_header*)(data + 14 + sizeof(ip_header) - sizeof(u_int));
        //printf("DEST PORT = %d \n", uh->dport);
        if (ntohs(uh->dport) == 53){
            //printf("DEST PORT = %d \n", ntohs(uh->dport));
            const u_char* payload =(const u_char*) (data + 14 + sizeof(ip_header) - sizeof(u_int) + sizeof(udp_header));
            payload += 20;
            printf("Packet DNS: %s \n", payload);
        }
    }
}

const char* PcapDnsProcessing::rleDecompress(const u_char* payload){
    int count;
    char c;
    int TOTAL = 0;
    while (*payload != '\0' && TOTAL != 42)
    {
        count = *(payload++);
        c = *(reinterpret_cast<const char*>(payload++));
        for (int i = 0; i < count; i++)
        {
            printf("%c", c);
            std::cout<<std::flush;
        }
        TOTAL++;
    }
    return NULL;
}

void PcapDnsProcessing::setActive(bool active){
    mActive = active;
}

bool PcapDnsProcessing::isDnsRequest(ip_header ih, udp_header uh){
    return false;
}