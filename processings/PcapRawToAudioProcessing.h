//
//  PcapRowToAudioProcessing.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 25/03/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__PcapRawToAudioProcessing__
#define __LibLoAndCap__PcapRawToAudioProcessing__

#include <iostream>
#include "PcapProcessings.h"
#include "portaudio.h"
#include <fstream> 
#include <vector>
#include <fstream> 
typedef struct
{
    float left_phase;
    float right_phase;
}
paTestData;
class PcapRawToAudioProcessing : public PcapProcessings{
public:
    
    PcapRawToAudioProcessing();
    ~PcapRawToAudioProcessing();
    void process (const u_char* data);
    void setActive(bool active);
    paTestData *data;
    std::vector <float>* music;
private:
    PaStreamParameters outputParameters;
    PaStream *stream = NULL;
    PaError err;
    const std::string s ="/Users/ludoviclaffineur/Music/Logic/testAudioNetwork/Bounces/BROLMAUVAI.aif";

    unsigned int bitCount (const u_char* value);


};

#endif /* defined(__LibLoAndCap__PcapRowToAudioProcessing__) */
