//
//  PcapIpProcessing.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 13/03/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "PcapIpProcessing.h"
#include "IpHeaderDefinitions.h"

PcapIpProcessing::PcapIpProcessing(Grid* g){
    mGrid = g;
     mGrid->addInput("PacketLength", 1, 65535, -1, 0, Converter::LINEAR);
}

void PcapIpProcessing::setActive(bool active){
    mActive = active;

}
void PcapIpProcessing::process(const u_char *datas){
    ip_header *ih;
    ih = (ip_header *) (datas + 14);
    mGrid->getInputWithName("PacketLength")->setValue(ih->tlen);
}