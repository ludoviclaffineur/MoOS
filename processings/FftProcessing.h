//
//  FFTprocessing.h
//  fftproc
//
//  Created by Louis Commere on 21/11/14.
//  Copyright (c) 2014 Louis Commere. All rights reserved.
//

#ifndef fftproc_FFTprocessing_h
#define fftproc_FFTprocessing_h

#include "vector"
#include <iostream>
#include <math.h>
#include <unistd.h>
#include "Processings.h"
#include "Grid.h"

class FFTprocessing : public Processings{
    
public:
    
    FFTprocessing(Grid* g, float sampleRate, int windowsSize);
    FFTprocessing(float sampleRate, int windowSize);
    void fft(float* window);
    void print();
    void process(float* window);


    void process(void* vdata){
        process (*((float**) vdata));
    };
        void setActive(bool active){mActive = active;};
    
    
private:
    std::vector<float> sp;
    void setSetter(int nbrSetter,...){};
    float mSampleRate;
    int mWindowSize;
    Setter<float>** mFrequenciesAmplitudes ;

    
};

#endif
