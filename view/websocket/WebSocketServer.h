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
#include "LeapMotionHandler.h"
#include "ReadWavFileHandler.h"
#include "OdbcHandler.h"
#include "SerialHandler.h"
#include "PcapHandler.h"
#include "OscHandler.h"
#include "MidiHandler.h"
#include "MidiNoteHandler.h"
#include "MidiNoteKeyHandler.h"
#include "MidiNoteDurationHandler.h"
#include "MidiNoteVelocityHandler.h"
#include "MidiControlChange.h"
#include "VideoOpenCvHandler.h"

#include "Grid.h"
#include "CaptureDevice.h"

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

    void dispatchRequest(message_ptr msg);
    void sendStopMessage();

private:
    void sendDescription();
    int mTypeOfCaptureDevice;
    int mListenningPort;
    int mDefaultOutput;
    void sendMidiPorts();
    void setMidiPort(int identifier);
    void trigGrid();
    server      mServer;
    pthread_t mThread;
    websocketpp::connection_hdl mConnectionHandler;
    void sendMessage(boost::property_tree::ptree ptree);
    void sendInit();
    CaptureDevice* mCaptureDevice;
    Grid* mGrid;
    void setCaptureDevice(int identifier);
    void setConfigurationPcap(int identifier);
    void sendConfigurationCaptureDevice();
    void sendOutputList();
    void sendGoToOutputs();
    void setDefaultOutput(int identifier);
    void sendGrid();
    void setRow(int identifier);
    int mCurrentRow;
    boost::property_tree::ptree getJsonOutputs();
    boost::property_tree::ptree getJsonInputs();
    boost::property_tree::ptree getJsonWeights();
    boost::property_tree::ptree getJsonRowsData();
    void setWeightForCell(std::string inputName, std::string outputName, float weight);

    MidiHandler* mMidiHandler;
    bool isConfigured;

    void sendPcapInterfaces(pcap_if_t* interfaces);
};
#endif /* defined(__LibLoAndCap__WebSocketServer__) */
