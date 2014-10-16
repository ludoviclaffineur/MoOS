//
//  ThreadHttpRequest.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 3/10/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__ThreadHttpRequest__
#define __LibLoAndCap__ThreadHttpRequest__

#include <stdio.h>
#include <pthread.h>
#include <string>
#include <vector>
#include <sstream>
#include "HttpClient.h"

struct httpReqAndData{
    std::string server;
    std::string path;
    std::string name;
};

class ThreadHttpRequest{

    
public:
    ThreadHttpRequest();
    void start();
    static void* run(void* user_data);
    void stop();
    //void push(httpReqAndData h);
    void push( std::string server, std::string path, std::string name);
    //~ThreadHttpRequest();


private:
    pthread_t http_thread, http_thread2;
    std::vector<httpReqAndData*> requestDataAndStore;
    bool isRunning;
    const int TOTAL_WAITING_LIST = 3000;
};

#endif /* defined(__LibLoAndCap__ThreadHttpRequest__) */
