//
//  MidiKeyHandler.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 20/01/15.
//  Copyright (c) 2015 Ludovic Laffineur. All rights reserved.
//

#include "MidiNoteKeyHandler.h"
MidiNoteKeyHandler::MidiNoteKeyHandler(MidiNoteHandler* mh):OutputsHandler("MidiKey"){
    mMidiNoteHandler = mh;
    mOutputType = CONSTANCES::MIDI;
    mConverter = new Converter(Converter::TypeOfExtrapolation::LINEAR, 0.0,1.0,111, 33);
    //mConverter = new Converter
}

bool MidiNoteKeyHandler::sendData(){
    std::cout << "KEY SENT" <<mValueBeforeSending<< std::endl;
        mMidiNoteHandler->setKey(mValueBeforeSending);
    return true;
}

void MidiNoteKeyHandler::setParameters(std::vector<std::string> ParameterList){
}