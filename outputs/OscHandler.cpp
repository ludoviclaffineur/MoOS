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

OscHandler::OscHandler(const char* n, const char* ipAddress, const char* port, const char* oscAddress, const char* oscTag ):OutputsHandler(n){

    mIpAddress = new char [strlen(ipAddress) + 1];
    strcpy(mIpAddress, ipAddress);

    mPort = new char [strlen(port) + 1];
    strcpy(mPort, port);

    mOscAddress = new char [strlen(oscAddress) + 1];
    strcpy(mOscAddress, oscAddress);

    mOscTag = new char [strlen(oscTag) + 1];
    strcpy(mOscTag , oscTag);

    mDistant = lo_address_new(mIpAddress, mPort);
    mParamNumber = 0;
    mValueBeforeSending = 0;

    mParameters.push_back(new Parameter<char**>("IP Address", &mIpAddress));
    mParameters.push_back(new Parameter<char**>("Port", &mPort));
    mParameters.push_back(new Parameter<char**>("Osc Address Pattern", &mOscAddress));
    mParameters.push_back(new Parameter<char**>("Osc Tag", &mOscTag));
    mParameters.push_back(new Parameter<int*>("tag i value", &mParamNumber));

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

bool OscHandler::setIpAdress(const char* newIp){
    setTabChar(mIpAddress, newIp);
    lo_address osc = mDistant;
    mDistant = NULL;
    lo_address_free(osc);
	return mDistant = lo_address_new(mIpAddress, mPort);
}

const char* OscHandler::getIpAdress() const{
    return mIpAddress;
}

bool OscHandler::setOscAddress(const char* newOscAddress){
    return setTabChar(mOscAddress, newOscAddress);
}

const char* OscHandler::getOscAddress() const{
    return mOscAddress;
}

bool OscHandler::setPort(const char* newPort){
    setTabChar(mPort, newPort);
    lo_address osc = mDistant;
    mDistant = NULL;
    lo_address_free(osc);
	return mDistant = lo_address_new(mIpAddress, mPort);
}
const char* OscHandler::getPort() const{
    return mPort;
}

bool OscHandler::setOscTag(const char* newOscTag){
    return setTabChar(mOscTag, newOscTag);
}

const char* OscHandler::getOscTag() const{
    return mOscTag;
}


bool OscHandler::setTabChar(char* target, const char* newValue){
    if(target){
        delete target;
    }
    target = new char [strlen(newValue) + 1];
    return(strcpy(target, newValue));
}
OscHandler::~OscHandler(){
    delete mOscTag;
    delete mOscAddress;
    delete mIpAddress;
    delete mPort;
}