//
//  WebSocketServer.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 8/01/15.
//  Copyright (c) 2015 Ludovic Laffineur. All rights reserved.
//

#include "WebSocketServer.h"
#include <boost/thread.hpp>

/*

|Opcode  | Meaning                             | Reference |
-+--------+-------------------------------------+-----------|
| 0      | Continuation Frame                  | RFC 6455  |
-+--------+-------------------------------------+-----------|
| 1      | Text Frame                          | RFC 6455  |
-+--------+-------------------------------------+-----------|
| 2      | Binary Frame                        | RFC 6455  |
-+--------+-------------------------------------+-----------|
| 8      | Connection Close Frame              | RFC 6455  |
-+--------+-------------------------------------+-----------|
| 9      | Ping Frame                          | RFC 6455  |
-+--------+-------------------------------------+-----------|
| 10     | Pong Frame                          | RFC 6455  |
-+--------+-------------------------------------+-----------|

*/



void WebSocketServer::onMessage(WebSocketServer* ws, websocketpp::connection_hdl hdl, message_ptr msg){
    ws->mConnectionHandler = hdl;
    std::cout<<"I am HERE" <<std::endl;
}


WebSocketServer::WebSocketServer(int port){
    mServer = new server();
    mListenningPort = port;
    try{
        mServer->set_access_channels(websocketpp::log::alevel::none);
        mServer->clear_access_channels(websocketpp::log::alevel::frame_payload);
        mServer->init_asio();

        // Register our message handler
        mServer->set_message_handler(bind(&WebSocketServer::onMessage,this,::_1,::_2));
        mServer->listen(port);
        mServer->start_accept();
    }
    catch (const std::exception & e) {
        std::cout << e.what() << std::endl;
    } catch (websocketpp::lib::error_code e) {
        std::cout << e.message() << std::endl;
    } catch (...) {
        std::cout << "other exception" << std::endl;
    }

}

WebSocketServer::~WebSocketServer(){
    mServer->stop();
    delete mServer;
}



void WebSocketServer::sendMessage(std::vector<Input*>* inputs){
    std::string JsonArray = inputsToJson(inputs);
    try {
        mServer->send(mConnectionHandler, JsonArray, websocketpp::frame::opcode::TEXT);
    } catch (const websocketpp::lib::error_code& e) {
        std::cout << "Echo failed because: " << e
        << "(" << e.message() << ")" << std::endl;
    }

}

std::string WebSocketServer::inputsToJson(std::vector<Input*>* inputs){
    using boost::property_tree::ptree;
    ptree pt;
    ptree children;
    ptree child1, child2, child3;
    for(int i=0; i<inputs->size();i++){
        child1.put(inputs->at(i)->getName(),inputs->at(i)->getExtrapolatedValue());
    }



    pt.put("testkey", "testvalue");
    pt.add_child("InputsDictonnary", child1);
    std::stringstream ss;
    write_json(ss, child1);
    std::string my_string_to_send_somewhere_else = ss.str();
    return my_string_to_send_somewhere_else;
}

void WebSocketServer::start(){
    try{
        pthread_create(&mThread,NULL,WebSocketServer::run,this);
    }
    catch (...) {
        std::cout << "other exception" << std::endl;
    }
}

void* WebSocketServer::run(void* userData){
    WebSocketServer* s = (WebSocketServer*) userData;
    s->mServer->run();
    return nullptr;
}

void WebSocketServer::stop(){

}
