//
//  MidiControlChange.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 21/01/15.
//  Copyright (c) 2015 Ludovic Laffineur. All rights reserved.
//

#include "MidiControlChange.h"


MidiControlChange::MidiControlChange(MidiHandler* mh, std::string name): OutputsHandler(name.c_str()){
    mOutputType = CONSTANCES::MIDI;
    mMidiHandler = mh;
    mController = 1;
    mConverter = new Converter(Converter::TypeOfExtrapolation::LINEAR, 0.0,1.0,0.0, 127);
    mParameters.push_back(new Parameter<unsigned short>("cc", &mController));
    mParameters.push_back(new Parameter<int>("OutputType", &mOutputType));
}

MidiControlChange::MidiControlChange(MidiHandler* mh, int controller,std::string name): MidiControlChange(mh,name){
    mController = controller;
}


bool MidiControlChange::sendData(){
    mMidiHandler->sendControlChange(mController, mValueBeforeSending);
    return true;
}
void MidiControlChange::setParameters(std::vector<std::string> ParameterList){
    for (int i=0; i<ParameterList.size(); i++) {
        if (ParameterList.at(i).compare("Name")==0) {
            OutputsHandler::setName(ParameterList.at(i+1).c_str());
        }
        else if (ParameterList.at(i).compare("cc")==0) {
            setControllerId(std::atoi(ParameterList.at(i+1).c_str()));
        }
    }
}

void MidiControlChange::setControllerId(unsigned char newController){
    mController = newController;
}