//
//  GranularSyntheziser.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 12/12/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__GranularSyntheziser__
#define __LibLoAndCap__GranularSyntheziser__

#include <stdio.h>
#include "Grid.h"
#include "portaudio.h"
#include "Grain.h";
typedef struct
{
    float left_phase;
    float right_phase;
}
paTestData;

class GranularSyntheziser{


public:

    GranularSyntheziser(Grid* g);
    ~GranularSyntheziser();
    int getDuration();
    void setDuration(int duration);

    int getOverlap();
    void setOverlap(int overlap);

    float getVolume();
    void setVolume(float volume);

    paTestData *data;
    float getSample();
    std::vector <float>* music;
    std::vector <short>mAudioWave ;
     std::vector <Grain*>mGrains ;
    

private:
    int mDuration;

    int mOverlap;
    float mVolume;
    PaStream *stream;
    bool loadWave(std::string path);





};


#endif /* defined(__LibLoAndCap__GranularSyntheziser__) */
