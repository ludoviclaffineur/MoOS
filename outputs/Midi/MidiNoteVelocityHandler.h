//
//  MidiNoteVelocityHandler.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 20/01/15.
//  Copyright (c) 2015 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__MidiNoteVelocityHandler__
#define __LibLoAndCap__MidiNoteVelocityHandler__

#include <stdio.h>
#include "OutputsHandler.h"
#include "MidiNoteHandler.h"
#include "AppIncludes.h"

class MidiNoteVelocityHandler : public OutputsHandler{
public:
    MidiNoteVelocityHandler(MidiNoteHandler* mh);
    bool sendData();
    void setParameters(std::vector<std::string> ParameterList);
private:
    MidiNoteHandler* mMidiNoteHandler;
};

#endif /* defined(__LibLoAndCap__MidiNoteVelocityHandler__) */
