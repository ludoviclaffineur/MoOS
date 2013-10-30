//
//  main.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 30/10/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#include "AppIncludes.h"

int main(int argc, const char * argv[])
{
    lo_address add = lo_address_new("127.0.0.1", "1234");
    lo_send(add,"/fader","i",2);
    PcapHandler _pcap = PcapHandler();
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t* alldevs, *d;
    _pcap.FindAllDevs(&alldevs, errbuf);
    int i=0;
    for( d=alldevs; d; d=d->next)
	{
        
		printf("%d. %s", ++i, d->name);
		if (d->description)
			printf(" (%s)\n", d->description);
		else
			printf(" (No description available)\n");
	}
    // insert code here...
    OscHandler oscSender = OscHandler();
    if(oscSender.SendData(3, 4)){
        std::cout << "MESSAGE SENT";
    }
    qmsldk;
    mqlskdmqlskdmlsdkqd;
    Converter c = Converter();
    c.Extrapolate(2);
    printf("c extra %f \n", c.Extrapolate(3.0));
    qsdqmlsdkqsmdlkqsmdk;
    qsdmqlsdkqmsdlkqmlskdmq
    qmlsdkqmsdlkqmsdkqmsd
    qmlsdkmqsldkmqsdksqml
    mlqskdmlqskd
    return 0;
}

