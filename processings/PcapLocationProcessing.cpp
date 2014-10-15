//
//  PcapLocationProcessing.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 13/03/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "PcapLocationProcessing.h"
#include "IpHeaderDefinitions.h"

PcapLocationProcessing::PcapLocationProcessing(Grid* g){
    std::string csvstring ="/Users/ludoviclaffineur/Documents/LibLoAndCap/build/Release/IpGps.csv";
    mIpLocations = CsvImporter::importCsv(csvstring);
    if (mIpLocations == NULL){
        mActive = false;
    }
    else{
        mActive = true;
        mGrid = g;
        mGrid->addInput("SourceLatitude", 90, -90, -1, 0, Converter::LINEAR);
        mGrid->addInput("SourceLongitude", -180, 180, -1, 0, Converter::LINEAR);
        mGrid->addInput("DestLatitude", 90, -90, -1, 0, Converter::LINEAR);
        mGrid->addInput("DestLongitude", -180, 180, -1, 0, Converter::LINEAR);

        //mSetDestinationLattitude = &Input::setValue;
        mSetterSourceLat = mGrid->getInputWithName("SourceLatitude");
        mSetterSourceLong = mGrid->getInputWithName("SourceLongitude");
        mSetterDestLat= mGrid->getInputWithName("DestLatitude");
        mSetterDestLong = mGrid->getInputWithName("DestLongitude");
        //mSetDestinationLattitude(*mSetterSourceLat, 0.2);
       // mSetterSourceLat->setValue(0.2);
    }
}

void PcapLocationProcessing::setActive(bool active){
    mActive = active;
}


void PcapLocationProcessing::setSetter(int nbrSetter,...){
    va_list ap;
    va_start(ap, nbrSetter);

    mSetterSourceLat = va_arg(ap, Setter<float>*);
    mSetterSourceLong = va_arg(ap, Setter<float>*);
    mSetterDestLat = va_arg(ap, Setter<float>*);
    mSetterDestLong = va_arg(ap, Setter<float>*);
    //mSetDestinationLongitude = va_arg(ap, SetterFct);
    
    va_end(ap);
}

PcapLocationProcessing::~PcapLocationProcessing(){
    for (int i = 0; i<NBR_IP_ADDRESSES; i++) {
        delete mIpLocations[i];
    }
    delete [] mIpLocations;
}


//void PcapLocationProcessing::process(const u_char *datas){
void PcapLocationProcessing::process(const u_char *data){
    if(isActive()) {
        ip_header *ih;
        ih = (ip_header *) (data + 14);
        long int ipadd =ntohl(ih->saddr.int_address);
        //std::cout<<"Adresse IP "<<ipadd <<std::endl;
        if(isLocalAddress(ipadd)){
            //std::cout<<"Je suis dedans" <<std::endl;
            mSetterSourceLat->setValue(51);
            mSetterSourceLong->setValue(4);
            ipadd = ntohl(ih->daddr.int_address);
            if( isLocalAddress(ipadd) ){
                mSetterDestLat->setValue(51);
                mSetterDestLong->setValue(4);
            }
            else{
                LocationIp* l = findLocationFromIpAddress(ipadd);
                if(l){
                    mSetterDestLat->setValue(l->getLatitude());
                    mSetterDestLong->setValue(l->getLongitude());
                }
            }
            //std::cout<< "LOCAL NETWORK"<< std::endl;
        }
        else{
            LocationIp* l = findLocationFromIpAddress(ntohl(ih->saddr.int_address));
            if(l){
                mSetterSourceLat->setValue(l->getLatitude());
                mSetterSourceLong->setValue(l->getLongitude());
                mSetterDestLat->setValue(51);
                mSetterDestLong->setValue(4);
                //std::cout<< "EXTERNAL NETWORK"<< std::endl;
            }
        }
    }
}

bool PcapLocationProcessing::isLocalAddress(long int ipadd){
    return ((ipadd > TEN_ZERO_ZERO_ZERO && ipadd <= TEN_FIFTY_TWO) || (ipadd > ONE_SEVENTY_TWO_MIN && ipadd <= ONE_SEVENTY_TWO_MAX) || (ipadd > ONE_NINETY_TWO_MIN && ipadd <= ONE_NINETY_TWO_MAX));
}


LocationIp* PcapLocationProcessing::findLocationFromIpAddress(unsigned long int TargetIp){
    return binaryTree(TargetIp);
    //return PcapHandler::Secante(TargetIp, p);
}

LocationIp* PcapLocationProcessing::binaryTree(unsigned long int TargetIp){
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

LocationIp* PcapLocationProcessing::secante(unsigned long int TargetIp){
    int x_2;
    int x_1 = 0;
    int x_0 = NBR_IP_ADDRESSES-1;
    for (int i=0;i<30;i++){
        x_2 = (float)x_1 - ((float)(x_1-x_0)/(float)(mIpLocations[x_1]->getIpBegin()-mIpLocations[x_0]->getIpBegin()))*(float)(mIpLocations[x_1]->getIpBegin()-TargetIp);

        if(mIpLocations[x_2]->getIpBegin() <=TargetIp &&mIpLocations[x_2+1]->getIpBegin() > TargetIp){
            std::cout<< "range trouvé  "<<mIpLocations[x_2]->getIpBegin() << "--"<< mIpLocations[x_2+1]->getIpBegin() <<std::endl;
            std::cout<< "Target  "<<TargetIp <<std::endl;
            std::cout<< "Nbr iteration  " << i <<std::endl ;
            return mIpLocations[x_2];
        }
        else{
            x_0 = x_1;
            x_1 = x_2;
        }
    }
    return NULL;
}