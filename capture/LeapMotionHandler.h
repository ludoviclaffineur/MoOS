//
//  LeapMotionHandler.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 4/11/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__LeapMotionHandler__
#define __LibLoAndCap__LeapMotionHandler__

#include "CaptureDevice.h"
#include "Grid.h"
#include <leap/Leap.h>

using namespace Leap;


class LeapMotionListener : public Listener {
public:
    LeapMotionListener(std::vector <Processings*>* processings);
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onExit(const Controller&);
    virtual void onFrame(const Controller&);
    virtual void onFocusGained(const Controller&);
    virtual void onFocusLost(const Controller&);
    virtual void onDeviceChange(const Controller&);
    virtual void onServiceConnect(const Controller&);
    virtual void onServiceDisconnect(const Controller&);

private:
    std::vector <Processings*>* mProcessings;
};



class LeapMotionHandler : public CaptureDevice, public Listener{
public:
    void init();
    LeapMotionHandler(Grid* g);
    ~LeapMotionHandler();

private:
    LeapMotionListener* listener;
    Leap::Controller* controller;
};
#endif /* defined(__LibLoAndCap__LeapMotionHandler__) */
