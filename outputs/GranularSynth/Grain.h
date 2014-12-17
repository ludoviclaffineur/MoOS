//
//  Grain.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 12/12/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__Grain__
#define __LibLoAndCap__Grain__

#include <stdio.h>
#include <vector>
class Grain{
public:
    Grain(std::vector<float>* audioFile, int duration, int blank,int initPos);
    float getSample();
    enum ENVELOPE{
        ATTACK=0,
        DELAY,
        RELEASE,
        STOP,
    };
    int mEnvelope;
    int mDuration;
    int mCurrentPostion;
    int mInitPostion;
    const int nbrSamplesFade = 20;
    std::vector<float>* mAudioFile;
    bool isDone(){
        return done;
    }
    bool done;
    int mBlank;
    int mWindowSize;
};
#endif /* defined(__LibLoAndCap__Grain__) */
