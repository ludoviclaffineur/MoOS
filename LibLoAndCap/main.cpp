//
//  main.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 30/10/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#include "AppIncludes.h"

void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);

Grid* TheGrid;
int main(int argc, const char * argv[])
{
    TheGrid = new Grid();
    PcapHandler _pcap = PcapHandler("ip and dst host 172.30.8.13", TheGrid);
    pcap_t *handle;
    const char* osc1= "OSC1";
    OscHandler oscSender= OscHandler(osc1);
    TheGrid->AddOutput(&oscSender);
    TheGrid->AddCell("PacketLength", "OSC1", 1.0);
	handle = _pcap.ListAndChooseInterface();
    //Converter c = Converter(Converter::EXPONENTIAL, 1, 65536, 0, 1);
    //std::cout<< c.Extrapolate(1)<<std::endl;

    //for(int i = 0; i<65000;i++){
      //  std::cout<< c.Extrapolate(i)<<std::endl;
    //}
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
    //Converter c = Converter(Converter::EXPONENTIAL, 0, 65536, 0, 1);
    //const char* name = ;
    //std::cout<< uh->len<< std::endl;
    TheGrid->GetInputWithName("PacketLength")->SetValue((float)uh->len);
    TheGrid->Compute();
}

