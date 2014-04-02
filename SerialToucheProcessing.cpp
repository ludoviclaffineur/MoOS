//
//  SerialToucheProcessing.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 2/04/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "SerialToucheProcessing.h"

SerialToucheProcessing::SerialToucheProcessing(){

}

void SerialToucheProcessing::process(size_char_tab data){
    for (int i =0;i<data.size;i++){

        if (*data.tab ==0){

            strucData = (commandData*) data.tab;
            //std::cout<<std::endl;
            char checksum=1;

            checksum+= strucData->command;
            checksum+= strucData->upper_x;
            checksum+= strucData->upper_y;
            checksum+= strucData->lower_x;
            checksum+= strucData->lower_y;
            checksum+= strucData->zeroByte;
            checksum = checksum%255;
            if(checksum == strucData->checkSum){
                printf("%hhX , %hhX \n", checksum,strucData->checkSum);;
                mSerialCount=0;
                //for(int j = 0; j<8; j++){
                // printf("%hhX , %hhx , %hhX\n",strucData->command, strucData->lower_x , strucData->zeroByte );            //}
                //std::cout<<std::endl;
                data.tab += 7 ;

                u_int16_t x = 0;
                x = strucData->upper_x<<8 | strucData->lower_x;

                int soustracX=0, soustracY=0;
                if ((strucData->zeroByte & 0x08) == 0x08){
                    soustracX += 256;
                }
                if ((strucData->zeroByte & 0x04) == 0x04){
                    soustracX += 1;
                }
                if ((strucData->zeroByte & 0x02) == 0x02){
                    soustracY += 256;
                }
                if ((strucData->zeroByte & 0x01) == 0x01){
                    soustracY += 1;
                }
                x-=soustracX;
                
                printf("%d , %hhX \n", x, strucData->zeroByte);
                i+=7;
            }
        }
        data.tab++;
        //2data.tab++;
       // mReceivedData[mSerialCount++] = (short unsigned int) data.tab[i];
       //printf("%hhX ", *data.tab);
        
    }

}

void SerialToucheProcessing::setActive( bool active ) {
    mActive = active;
}
