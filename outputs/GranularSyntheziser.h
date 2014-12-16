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
#include "Grain.h"
#include <deque>
typedef struct
{
    float left_phase;
    float right_phase;
}
paTestData;

class GranularSyntheziser{

public:

    GranularSyntheziser();
    ~GranularSyntheziser();
    int getDuration();
    void setDuration(int duration);

    int getOverlap();
    void setOverlap(int overlap);

    float getVolume();
    void setVolume(float volume);

    void setBlank(int blank);
    void setDecay(float decay);
    inline float getDecay();

    void setDelay(int delay);
    inline int getDelay();

    paTestData *data;
    float getSample();
    std::vector <float>* music;
    std::vector <float>* mAudioWave;
    std::vector <Grain*>mGrains ;
    inline void flushAudioWave();
    static float reverb(std::vector <float>* mAudioWave, float sample, int delay, float decay );
    static float echo(std::vector <float>* mAudioWave, float sample, int delay, float decay );
    static float lowPassFilter(std::vector <float>* mAudioWave, float sample, float cutoff );

private:
    int mDuration;
    int mBlank;
    int mPosition;
    int mOverlap;
    float mVolume;
    float mDecay;
    int mDelay;
    PaStream *stream;

    bool loadWave(std::string path);
};


#endif /* defined(__LibLoAndCap__GranularSyntheziser__) */
