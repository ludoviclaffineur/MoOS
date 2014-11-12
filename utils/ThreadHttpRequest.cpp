//
//  ThreadHttpRequest.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 3/10/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "ThreadHttpRequest.h"



ThreadHttpRequest::ThreadHttpRequest(){
    isRunning = false;
}


void ThreadHttpRequest::start(){
    isRunning = true;
    pthread_create(&http_thread, NULL, ThreadHttpRequest::run, this);
    //pthread_create(&http_thread2, NULL, ThreadHttpRequest::run, this);
}

void* ThreadHttpRequest::run(void *user_data){
    ThreadHttpRequest* ht = (ThreadHttpRequest*) user_data;
    while (ht->isRunning) {
        boost::asio::io_service io_service;

        std::stringstream fileNameSS;
        if (!ht->requestDataAndStore.empty()){
            httpReqAndData* h = ht->requestDataAndStore.front();
            ht->requestDataAndStore.erase(ht->requestDataAndStore.begin());
            try{
                client c(io_service, h->server, h->path, h->name);
            }
            catch(boost::exception& ex){

            }


        }
        else{
            sleep(1);
        }

    }
    return NULL;
}

void ThreadHttpRequest::push( std::string server, std::string path, std::string name){
    if (requestDataAndStore.size()< TOTAL_WAITING_LIST) {
        httpReqAndData* h  = new httpReqAndData;
        h->server = server;
        h->path = path;
        h->name = name;
        requestDataAndStore.push_back(h);
        std::cout<< "SIZE LIST: " << requestDataAndStore.size() <<std::endl;
    }

}