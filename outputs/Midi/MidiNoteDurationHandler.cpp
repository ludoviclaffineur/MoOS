//
//  MidiNoteDurationHandler.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 20/01/15.
//  Copyright (c) 2015 Ludovic Laffineur. All rights reserved.
//

#include "MidiNoteDurationHandler.h"

MidiNoteDurationHandler::MidiNoteDurationHandler(MidiNoteHandler* mh):
    OutputsHandler("Duration"){
    mOutputType = CONSTANCES::MIDI;
    mMidiNoteHandler = mh;
    mConverter = new Converter(Converter::TypeOfExtrapolation::LINEAR, 0.0,1.0,0.0, 5000);    //mConverter = new Converter
}

bool MidiNoteDurationHandler::sendData(){

    mMidiNoteHandler->setDuration(mValueBeforeSending);
    mMidiNoteHandler->sendMidiOnOff();
   
    return true;
}

void MidiNoteDurationHandler::setParameters(std::vector<std::string> ParameterList){
}