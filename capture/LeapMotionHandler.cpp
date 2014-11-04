//
//  LeapMotionHandler.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 4/11/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "LeapMotionHandler.h"
#include "LeapHandsProcessing.h"

const std::string fingerNames[] = {"Thumb", "Index", "Middle", "Ring", "Pinky"};
const std::string boneNames[] = {"Metacarpal", "Proximal", "Middle", "Distal"};
const std::string stateNames[] = {"STATE_INVALID", "STATE_START", "STATE_UPDATE", "STATE_END"};

LeapMotionHandler::LeapMotionHandler(Grid* g){
    mGrid = g;
    mProcessings.push_back(new LeapHandsProcessing());
    controller = new Controller();
    listener = new LeapMotionListener(&mProcessings);
}

LeapMotionHandler::~LeapMotionHandler(){
    controller->removeListener(*listener);
}

void LeapMotionHandler::init(){
    std::cout << "J'init le LEAP et add LISTENER" << std::endl;
    //Listener l;
    controller->addListener(*listener);
    //controller.
    std::cin.get();
}



LeapMotionListener::LeapMotionListener(std::vector <Processings*>* processings): Listener(){
    //Listener(*this);
    std::cout<< "Je suis dans le constructeur" <<std::endl;;
    mProcessings = processings;
}

void LeapMotionListener::onInit(const Controller& controller) {
    std::cout << "Initialized" << std::endl;
}

void LeapMotionListener::onConnect(const Controller& controller) {
    std::cout << "Connected" << std::endl;
    controller.enableGesture(Gesture::TYPE_CIRCLE);
    controller.enableGesture(Gesture::TYPE_KEY_TAP);
    controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
    controller.enableGesture(Gesture::TYPE_SWIPE);
}

void LeapMotionListener::onDisconnect(const Controller& controller) {
    // Note: not dispatched when running in a debugger.
    std::cout << "Disconnected" << std::endl;
}

void LeapMotionListener::onExit(const Controller& controller) {
    std::cout << "Exited" << std::endl;
}

void LeapMotionListener::onFrame(const Controller& controller) {
    const Frame frame = controller.frame();
    //std::cout <<" NEW FRAME" <<std::endl;
    std::vector<Processings*>::iterator i = mProcessings->begin();
    for (i= mProcessings->begin(); i!=mProcessings->end();i++ ) {
        (*i)->process((void*)&controller);
    }


}

void LeapMotionListener::onFocusGained(const Controller& controller) {
    std::cout << "Focus Gained" << std::endl;
}

void LeapMotionListener::onFocusLost(const Controller& controller) {
    std::cout << "Focus Lost" << std::endl;
}

void LeapMotionListener::onDeviceChange(const Controller& controller) {
    std::cout << "Device Changed" << std::endl;
    const DeviceList devices = controller.devices();

    for (int i = 0; i < devices.count(); ++i) {
        std::cout << "id: " << devices[i].toString() << std::endl;
        std::cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
    }
}

void LeapMotionListener::onServiceConnect(const Controller& controller) {
    std::cout << "Service Connected" << std::endl;
}

void LeapMotionListener::onServiceDisconnect(const Controller& controller) {
    std::cout << "Service Disconnected" << std::endl;
}