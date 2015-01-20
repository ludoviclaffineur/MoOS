//
//  MidiNoteVelocityHandler.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 20/01/15.
//  Copyright (c) 2015 Ludovic Laffineur. All rights reserved.
//

#include "MidiNoteVelocityHandler.h"

MidiNoteVelocityHandler::MidiNoteVelocityHandler(MidiNoteHandler* mh): OutputsHandler("MidiVelocity"){
    mMidiNoteHandler = mh;
    mConverter = new Converter(Converter::TypeOfExtrapolation::LINEAR, 0.0,1.0,0.0, 127);
    //mConverter = new Converter
}

bool MidiNoteVelocityHandler::sendData(){
    //mConverter.extrapolate(mValueBeforeSending)
    mMidiNoteHandler->setVelocity(mValueBeforeSending);
    return true;
}

void MidiNoteVelocityHandler::setParameters(std::vector<std::string> ParameterList){
}