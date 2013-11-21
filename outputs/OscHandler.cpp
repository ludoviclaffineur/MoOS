//
//  Osc.cpp
//  libpcapTest
//
//  Created by Ludovic Laffineur on 29/10/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#include "OscHandler.h"

OscHandler::OscHandler(){
    _distant = lo_address_new("127.0.0.1", "57120");
    _ParamNumber = 0;
    _ValueBeforeSending = 0;
}

OscHandler::OscHandler(const char* n):OutputsHandler(n){

    _distant = lo_address_new("127.0.0.1", "57120");
    _ParamNumber = 0;
    _ValueBeforeSending = 0;
    printf("Name : %s", n);
    //strcpy(_Name,n);
}

OscHandler::OscHandler(const char* ipAddress, const char* port){
    _distant = lo_address_new(ipAddress, port);
    _ParamNumber = 0;
    _ValueBeforeSending = 0;
}

bool OscHandler::SendData(){
    std::cout<< "Sent value" << _ValueBeforeSending<<std::endl;
    return lo_send(_distant,"/param", "if", _ParamNumber,_ValueBeforeSending);
}

bool OscHandler::SendData(int paramNumber, float value){
    return lo_send(_distant,"/param", "if", paramNumber,value);
}