//
//  Osc.cpp
//  libpcapTest
//
//  Created by Ludovic Laffineur on 29/10/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#include "OscHandler.h"

OscHandler::OscHandler(){
    mDistant = lo_address_new("127.0.0.1", "57120");
    mParamNumber = 0;
    mValueBeforeSending = 0;
}

OscHandler::OscHandler(const char* n):OutputsHandler(n){

    mDistant = lo_address_new("127.0.0.1", "57120");
    mParamNumber = 0;
    mValueBeforeSending = 0;
    //printf("Name : %s", n);
    //strcpy(_Name,n);
}

OscHandler::OscHandler(const char* ipAddress, const char* port){
    mDistant = lo_address_new(ipAddress, port);
    mParamNumber = 0;
    mValueBeforeSending = 0;
}

bool OscHandler::sendData(){
    //std::cout<< "Sent value" << _ValueBeforeSending<<std::endl;
    return lo_send(mDistant,"/param", "if", mParamNumber,mValueBeforeSending);
}

bool OscHandler::sendData(int paramNumber, float value){
    return lo_send(mDistant,"/param", "if", paramNumber,value);
}