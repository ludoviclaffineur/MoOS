//
//  MidiKeyHandler.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 20/01/15.
//  Copyright (c) 2015 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__MidiNoteKeyHandler__
#define __LibLoAndCap__MidiNoteKeyHandler__

#include <stdio.h>
#include "OutputsHandler.h"
#include "MidiNoteHandler.h"
#include "AppIncludes.h"

class MidiNoteKeyHandler : public OutputsHandler{
public:
    MidiNoteKeyHandler(MidiNoteHandler* mh);
    bool sendData();
    void setParameters(std::vector<std::string> ParameterList);

private:
    MidiNoteHandler* mMidiNoteHandler;
    void setMinKey(int minKey);
    void setMaxKey(int maxKey);
    int mMinKey;
    int mMaxKey;
    void updateConverter();
};


#endif /* defined(__LibLoAndCap__MidiKeyHandler__) */
