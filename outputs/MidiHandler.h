//
//  MidiHandler.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 20/01/15.
//  Copyright (c) 2015 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__MidiHandler__
#define __LibLoAndCap__MidiHandler__

#include <stdio.h>
#include "OutputsHandler.h"
#include "RtMidi.h"

class MidiHandler /*: public OutputsHandler*/{
public:
    MidiHandler();
    ~MidiHandler();
    void sendNoteOn(unsigned char key, unsigned char velocity);
    void sendNoteOff(unsigned char key, unsigned char velocity);
    void sendControlChange(unsigned char controller, unsigned char controllerValue );

    enum MIDI_COMMANDS{
        NOTE_OFF = 128,
        NOTE_ON = 144,
        AFTERTOUCH = 160,
        CONTINUOUS_CONTROLLER = 176,
        PATCH_CHANGE = 192,
        CHANNEL_PRESSURE = 208,
        PITCH_BEND = 224
    };
private:
    //RtMidiIn  *mMidiin = 0;
    RtMidiOut *mMidiOut = 0;
    void selectPort();

    
};


#endif /* defined(__LibLoAndCap__MidiHandler__) */
