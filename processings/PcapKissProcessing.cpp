
//  PcapKissProcessing.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 15/09/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "PcapKissProcessing.h"
#include "CsvImporter.h"
#include <math.h>

/// @brief The usual PI/180 constant
static const double DEG_TO_RAD = 0.017453292519943295769236907684886;
/// @brief Earth's quatratic mean radius for WGS-84
static const double EARTH_RADIUS_IN_METERS = 6372797.560856;

PcapKissProcessing::PcapKissProcessing(){
    std::string csvstring ="/Users/ludoviclaffineur/Documents/LibLoAndCap/CMAKE/IpGps.csv";
    mIpLocations = CsvImporter::importCsv(csvstring);
    if (mIpLocations == NULL){
        mActive = false;
    }
    else{
        mActive = true;
    }
}

void PcapKissProcessing::process(const u_char *data){
    if (mActive) {
        ip_header *ih;
        ih = (ip_header *) (data + 14);
        long int ipadd =ntohl(ih->saddr.int_address);
        ip_address i = ih->saddr;
        float distance = getDistance(data);
        int InOrOut;
        if( isLocalAddress(ipadd)){
            InOrOut = KISS::TRAFFIC::OUT;
            //mGrid->getInputWithName("DestLatitude")->setValue(51);
            //mGrid->getInputWithName("DestLongitude")->setValue(4);
        }
        else{
            InOrOut = KISS::TRAFFIC::IN;
            ipadd = ntohl(ih->daddr.int_address);
            i = ih->daddr;
        }

        if(isLocalAddress(ipadd)){


            Spectator* s = SpectatorWithIpAddress(ipadd);

            s->addPacket(InOrOut, ih->tlen, distance);

            if (s->getTime() +2 < time(NULL)) {
                std::cout<<"USERS " << (int)i.struct_bytes.byte1 <<"." << (int)i.struct_bytes.byte2 <<"." <<(int) i.struct_bytes.byte3 << "." <<(int) i.struct_bytes.byte4 <<" \tDISTANCE " << s->getMeanDistance() << "\t BANDWITH IN " << s->getBandwidthIn()/1024.0 << "\t BANDWITH OUT "<< s->getBandwidthOut()/ 1024.0<<std::endl;

                
                //i->struct_bytes.byte1;
                
                s->reset();
            }
        }

    }
}


Spectator* PcapKissProcessing::SpectatorWithIpAddress(long int ipadd){
    bool found=false;
    for (int i=0; i<audience.size(); i++) {
        if (audience[i]->getIpAdress() == ipadd) {
            found = true;
            return audience[i];
        }
    }
    Spectator* s= new Spectator((int)audience.size(),ipadd);
    audience.push_back(s);
    return s;
}

void PcapKissProcessing::setActive(bool active){
    mActive = active;
}

bool PcapKissProcessing::isLocalAddress(long int ipadd){
    return ((ipadd > TEN_ZERO_ZERO_ZERO && ipadd <= TEN_FIFTY_TWO) || (ipadd > ONE_SEVENTY_TWO_MIN && ipadd <= ONE_SEVENTY_TWO_MAX) || (ipadd > ONE_NINETY_TWO_MIN && ipadd <= ONE_NINETY_TWO_MAX));
}


float PcapKissProcessing::getDistance(const u_char *data){
    ip_header *ih;
    ih = (ip_header *) (data + 14);
    long int ipadd =ntohl(ih->saddr.int_address);
    //std::cout<<"Adresse IP "<<ipadd <<std::endl;

    LocationIp* from;
    LocationIp* to;
    if(isLocalAddress(ipadd)){
        //std::cout<<"Je suis dedans" <<std::endl;
        //mGrid->getInputWithName("SourceLatitude")->setValue(51);
        //mGrid->getInputWithName("SourceLongitude")->setValue(4);
        from = new LocationIp(ipadd, 51,  4);


        ipadd = ntohl(ih->daddr.int_address);
        if( isLocalAddress(ipadd) ){
            to = new LocationIp(ipadd, 51,  4);
            //mGrid->getInputWithName("DestLatitude")->setValue(51);
            //mGrid->getInputWithName("DestLongitude")->setValue(4);
        }
        else{
            LocationIp* l = findLocationFromIpAddress(ipadd);
            if(l){
                to = new LocationIp(ipadd, l->getLatitude(),  l->getLongitude());
                //mGrid->getInputWithName("DestLatitude")->setValue(l->getLatitude());
                //mGrid->getInputWithName("DestLongitude")->setValue(l->getLongitude());
            }
        }
        //std::cout<< "LOCAL NETWORK"<< std::endl;
    }
    else{
        LocationIp* l = findLocationFromIpAddress(ntohl(ih->saddr.int_address));
        if(l){
            to = new LocationIp(ipadd, 51,  4);
            from = new LocationIp(ipadd, l->getLatitude(),  l->getLongitude());
            //mGrid->getInputWithName("SourceLatitude")->setValue(l->getLatitude());
            //mGrid->getInputWithName("SourceLongitude")->setValue(l->getLongitude());
            //mGrid->getInputWithName("DestLatitude")->setValue(51);
            //mGrid->getInputWithName("DestLongitude")->setValue(4);
            //std::cout<< "EXTERNAL NETWORK"<< std::endl;
        }
    }
    if (from && to){
        return haversine(from, to);
    }
    else{
        return 0;
    }

}

LocationIp* PcapKissProcessing::findLocationFromIpAddress(unsigned long int TargetIp){
    return binaryTree(TargetIp);
    //return PcapHandler::Secante(TargetIp, p);
}

LocationIp* PcapKissProcessing::binaryTree(unsigned long int TargetIp){
    int min = 0, max = NBR_IP_ADDRESSES-1;
    int middle;
    int i;
    for( i = 0; i<30; i++){
        middle = (max+min)/2;
        if (TargetIp >= mIpLocations[middle]->getIpBegin() && TargetIp < mIpLocations[middle+1]->getIpBegin()) {
            //std::cout<<"Nbr iterations = " << i <<std::endl;
            return mIpLocations[middle];
        }
        else{
            if (TargetIp >= mIpLocations[middle]->getIpBegin() && TargetIp <= mIpLocations[max]->getIpBegin()) {
                min = middle;
            }
            else{
                max= middle;
            }
        }
    }

    return NULL;
}

float PcapKissProcessing::haversine (LocationIp* from, LocationIp* to){
    double latitudeArc  = (from->getLatitude() - to->getLatitude()) * DEG_TO_RAD;
    double longitudeArc = (from->getLongitude() - to->getLongitude()) * DEG_TO_RAD;
    double latitudeH = sin(latitudeArc * 0.5);
    latitudeH *= latitudeH;
    double lontitudeH = sin(longitudeArc * 0.5);
    lontitudeH *= lontitudeH;
    double tmp = cos(from->getLatitude()*DEG_TO_RAD) * cos(to->getLatitude()*DEG_TO_RAD);
    return 2.0 * asin(sqrt(latitudeH + tmp*lontitudeH))/3.1416;
}

