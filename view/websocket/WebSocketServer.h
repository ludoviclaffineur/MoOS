//
//  WebSocketServer.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 8/01/15.
//  Copyright (c) 2015 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__WebSocketServer__
#define __LibLoAndCap__WebSocketServer__

#include <stdio.h>
#include <websocketpp/config/asio_no_tls.hpp>

#include <websocketpp/server.hpp>
#include <sstream>
#include <iostream>
#include <vector>
#include "Input.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

class WebSocketServer{

public:
    typedef websocketpp::server<websocketpp::config::asio> server;
    typedef server::message_ptr message_ptr;
    WebSocketServer(int port);
    ~WebSocketServer();
    void start();
    void stop();
    static void onMessage(WebSocketServer* s, websocketpp::connection_hdl hdl, message_ptr msg);
    static void* run(void* userData);
    void sendMessage(std::vector<Input*>* inputs);
    std::string inputsToJson(std::vector<Input*>* inputs);
    
private:
    int mListenningPort;
    server* mServer;
    pthread_t mThread;
    websocketpp::connection_hdl mConnectionHandler;
};
#endif /* defined(__LibLoAndCap__WebSocketServer__) */
