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
}

OscHandler::OscHandler(const char* ipAddress, const char* port){
    _distant = lo_address_new(ipAddress, port);
}

bool OscHandler::SendData(int paramNumber, float value){
    return lo_send(_distant,"/param", "if", paramNumber,value);
}