//
//  MidiNoteDurationHandler.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 20/01/15.
//  Copyright (c) 2015 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__MidiNoteDurationHandler__
#define __LibLoAndCap__MidiNoteDurationHandler__

#include <stdio.h>
#include "OutputsHandler.h"
#include "MidiNoteHandler.h"
class MidiNoteDurationHandler : public OutputsHandler{
public:
    MidiNoteDurationHandler(MidiNoteHandler* mh);
    bool sendData();
    void setParameters(std::vector<std::string> ParameterList);
private:
    MidiNoteHandler* mMidiNoteHandler;
};

#endif /* defined(__LibLoAndCap__MidiNoteDurationHandler__) */
