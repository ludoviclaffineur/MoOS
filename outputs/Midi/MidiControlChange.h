//
//  MidiControlChange.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 21/01/15.
//  Copyright (c) 2015 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__MidiControlChange__
#define __LibLoAndCap__MidiControlChange__

#include <stdio.h>
#include "OutputsHandler.h"
#include "MidiHandler.h"


class MidiControlChange : public OutputsHandler{
public:
    MidiControlChange(MidiHandler* mh);
    bool sendData();
    void setControllerId(unsigned char newController);
    void setParameters(std::vector<std::string> ParameterList);
private:
    MidiHandler* mMidiHandler;
    unsigned short mController;
};

#endif /* defined(__LibLoAndCap__MidiControlChange__) */
