//
//  main.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 30/10/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#include "AppIncludes.h"

void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);
OscHandler oscSender;
int main(int argc, const char * argv[])
{
    PcapHandler _pcap = PcapHandler();
    pcap_t *handle;
    oscSender = OscHandler();
    
	handle = _pcap.ListAndChooseInterface();
    _pcap.Loop(handle, 0, packet_handler, NULL);
    return 0;
}

void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
    ip_header *ih;
	udp_header *uh;
	u_int ip_len;
	u_short sport,dport;
	time_t local_tv_sec;
    local_tv_sec = header->ts.tv_sec;
	//localtime_s(&ltime, &local_tv_sec);
	//strftime( timestr, sizeof timestr, "%H:%M:%S", &ltime);
    
	/* print timestamp and length of the packet */
	//printf("%s.%.6d len:%d ", timestr, header->ts.tv_usec, header->len);
    
	/* retireve the position of the ip header */
	ih = (ip_header *) (pkt_data +
                        14); //length of ethernet header
    
	/* retireve the position of the udp header */
	ip_len = (ih->ver_ihl & 0xf) * 4;
	uh = (udp_header *) ((u_char*)ih + ip_len);
    
	/* convert from network byte order to host byte order */
	sport = ntohs( uh->sport );
	dport = ntohs( uh->dport );
    Converter c = Converter(Converter::LOGARITHMIC, 2, 4, 7, 9);
    if(oscSender.SendData(0, uh->len)){
        std::cout<<"Message :" << uh->len <<std::endl;
    }
}

