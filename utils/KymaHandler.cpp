//
//  KymaHandler.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 5/05/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "KymaHandler.h"





void error(int num, const char *m, const char *path){
    printf("liblo server error %d in path %s: %s\n", num, path, m);
    fflush(stdout);
}


KymaHandler::KymaHandler(const char* ipAddress, const char* port, Grid* g){
    mAddress = lo_address_new(ipAddress,port);
    mServerOsc = lo_server_thread_new ("4500", error);
    mGrid = g;
    widgetId = 0;
    if (mServerOsc) {
        lo_server_thread_add_method(mServerOsc , "/osc/response_from", "i", responseFrom, this);
        lo_server_thread_add_method(mServerOsc , "/osc/widget", "is", receivedWidget, this);

        lo_server_thread_start(mServerOsc);
    }
    lo_send(mAddress, "/osc/respond_to_default", "i", 4500);

}

int KymaHandler::responseFrom(const char *path, const char *types, lo_arg **argv, int argc,void *data, void *user_data){
    KymaHandler* k = (KymaHandler*) user_data;
    printf("Received From %i \n", argv[0]->i);
    lo_send(k->mAddress, "/osc/widget", "i", k->widgetId++);
    return 1;
}

int KymaHandler::receivedWidget(const char *path, const char *types, lo_arg **argv, int argc,void *data, void *user_data){
    KymaHandler* k = (KymaHandler*) user_data;
    char*  c = &argv[1]->S;
    std::stringstream ss;
    ss << c;
    printf("%s\n", ss.str().c_str());
//    while (*c != '\0' ) {
//        printf("%c", *c);
//        c++;
//    }
    boost::property_tree::ptree pt;
    try
    {
        boost::property_tree::read_json(ss, pt);
    }
    catch (std::exception const& e)
    {
        //finished
        std::cerr << e.what() << "OK FINISHED"<<std::endl;
        return 0;
    }
    try
    {
        int minimum = pt.get<int>("minimum");
        int maximum = pt.get<int>("maximum");
        std::string label = pt.get<std::string>("label");
        int concreteEventID = pt.get<int>("concreteEventID");

        printf("minimum = %d, maximum = %d, name = %s , concreteID =%d \n", minimum, maximum, label.c_str(), concreteEventID);
        k->mGrid->addOutput(new OscHandler(label.c_str(), "172.30.8.11", "8000", "/vcs", "if",concreteEventID, minimum,maximum));
        lo_send(k->mAddress, "/osc/widget", "i", k->widgetId++);
    }
    catch (std::exception const& e)
    {
        lo_send(k->mAddress, "/osc/widget", "i", k->widgetId++);
        std::cerr << e.what() << std::endl;
    }


    printf("\n");
    return 1;
}
KymaHandler::~KymaHandler(){
    lo_server_thread_stop(mServerOsc);
    lo_server_thread_free(mServerOsc);
    //lo_server_free(mServerOsc);
}

