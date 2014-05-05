//
//  PcapDnsProcessing.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 24/04/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "PcapDnsProcessing.h"


PcapDnsProcessing::PcapDnsProcessing(){
    OscOutputParent = new OscHandler("DNS Parent ouputs","127.0.0.1", "20000", "/parentNode", "is");
    OscOutputChild = new OscHandler("DNS Child ouputs","127.0.0.1", "20000", "/childNode", "is");
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
            payload+=12;   // matches words beginning by "sub"

            std::stringstream s;
            s<< payload;
            //std::cout<<s.str() << std::endl;
            std::string theRequest = s.str();
            for (int i=0; i< theRequest.length(); i++) {
                if(theRequest[i] < '.'){
                    theRequest[i]='.';
                }
            }
            std::string token = theRequest.substr(0, theRequest.find_last_of('.'));

            //std::cout<<token << std::endl;
            //std::cout<< token.find_last_of(delimiter)<< " size: " << token.length()<<std::endl;

            token = token.substr(token.find_last_of('.')+1,token.length());
            std::cout<< "FINAL = " <<token<<std::endl;
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