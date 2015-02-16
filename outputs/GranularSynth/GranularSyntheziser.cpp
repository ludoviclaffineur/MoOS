//
//  GranularSyntheziser.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 12/12/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "GranularSyntheziser.h"
#include <fstream>
#include <math.h>
#define NUM_SECONDS   (40)
#define SAMPLE_RATE   (44100)

int patestCallback( const void *inputBuffer, void *outputBuffer,
                   unsigned long framesPerBuffer,
                   const PaStreamCallbackTimeInfo* timeInfo,
                   PaStreamCallbackFlags statusFlags,
                   void *userData )
{
    /* Cast data passed through stream to our structure. */
    GranularSyntheziser* ptr = (GranularSyntheziser*) userData;
    //paTestData *data = (paTestData*)userData;
    //std::vector <float>* mu =  ( std::vector <float>*) userData;
    float *out = (float*)outputBuffer;
    unsigned int i;
    (void) inputBuffer; /* Prevent unused variable warning. */
    static int parcour = 0;
    for( i=0; i<framesPerBuffer; i++ )
    {
        *out++ = (float) ptr->data->left_phase;
        *out++ = (float) ptr->data->right_phase;
        float sample = ptr->getSample();
        float reverbLevel = 0.2;
        //sample = GranularSyntheziser::reverb(ptr->mAudioWave, sample, 100, reverbLevel);
        sample = GranularSyntheziser::echo(ptr->mAudioWave, sample, ptr->getDelay(), ptr->getDecay());
        sample = GranularSyntheziser::lowPassFilter(ptr->mAudioWave, sample, ptr->getCutoff());
        sample = GranularSyntheziser::lowPassFilter(ptr->mAudioWave, sample, ptr->getCutoff());
        ptr->mAudioWave->push_back(sample);
        //std::cout<<sample<<std::endl;
        ptr->flushAudioWave();

        ptr->data->left_phase  = sample;
        ptr->data->right_phase = sample;
        //
    }
    //ptr->setDuration(ptr->getDuration()-5);


    return 0;
}

void GranularSyntheziser::setCutoff(float cutoff){
    mCutoff = cutoff;
}
float GranularSyntheziser::getCutoff(){
    return mCutoff;
}



void GranularSyntheziser::flushAudioWave(){
    if (mAudioWave->size()>=400*44.1){
        mAudioWave->erase(mAudioWave->begin()); //cost 15% CPU
    }

}

GranularSyntheziser::GranularSyntheziser(){
    PaStream *stream;
    PaError err;
    mCutoff = 0.0f;
    //mEnvelope = 0;
    //std::ifstream file(s, std::ifstream::in);
    music = new std::vector <float>();
    mAudioWave = new std::deque <float>();
    //char byte;
    /* while (file.good()) {
     byte = file.get();
     double a =((float)byte/128.0f);
     music->push_back(a);
     //printf(" %f ", (float)byte);
     }*/
    mInitPos = 0;
    mOverlap    = 3000.0f;
    mPosition   = 0.0;
    mDecay      = 0.0f;
    data = new paTestData;

    printf("PortAudio Test: output sawtooth wave.\n");
    /* Initialize our data for use by callback. */
    data->left_phase = data->right_phase = 0.0;
    /* Initialize library before making any other calls. */
    loadWave("/Users/ludoviclaffineur/Documents/LibLoAndCap/data/sound15.wav"); //15 OK

 //   mGrains.push_back(Grain(music, 2000 ,500));
   // mGrains.push_back(Grain(music, 3000,500 ));
    err = Pa_Initialize();

    printf("Erreur : %s", Pa_GetErrorText(err));
    /* Open an audio I/O stream. */
    err = Pa_OpenDefaultStream( &stream,
                               0,          /* no input channels */
                               2,          /* stereo output */
                               paFloat32,  /* 32 bit floating point output */
                               SAMPLE_RATE,
                               256,        /* frames per buffer */
                               patestCallback,
                               this );

    err = Pa_StartStream( stream );
    printf("Erreur : %s", Pa_GetErrorText(err));
    /* Sleep for several seconds. */
    //Pa_Sleep(NUM_SECONDS*1000);
}


GranularSyntheziser::~GranularSyntheziser(){
     Pa_StopStream( stream );
     Pa_CloseStream( stream );
    Pa_Terminate();
    printf("Test finished.\n");
}

float GranularSyntheziser::getSample(){
    float sampleResult = 0.0f;

    if(mGrains.size()==0 || mPosition++ > (mGrains[mGrains.size()-1]->mDuration+ mGrains[mGrains.size()-1]->mBlank- mOverlap)){
        if(mDuration >mOverlap){
            mGrains.push_back(new Grain(music, mDuration, mBlank, mInitPos));
        }
        mPosition = 0.0f;
    }

    if (mGrains.size()!=0) {
        if (mGrains[0]->isDone()){
            //std::cout<<"DELETE"<<std::endl;
            delete *mGrains.begin();
            mGrains.erase(mGrains.begin());
        }

        for(int i =0; i<mGrains.size();i++) {
            sampleResult += mGrains[i]->getSample();
        }

    }
    else{
        sampleResult=  0.0f;
    }
    return sampleResult;
    //return mGrains.front()->getSample();
}

float GranularSyntheziser::reverb(std::deque <float>* mAudioWave,float sample, float delay, float decay ){
    float returnSample = sample;
    for (int i = 0; i<200; i++) {
        returnSample = echo(mAudioWave,returnSample,(i*30)+delay,decay*exp(-(float)i));
    }
    return returnSample;
}

float GranularSyntheziser::lowPassFilter(std::deque <float>* mAudioWave, float sample, float cutoff){
    float RC = 1.0/(cutoff*2*3.14);
    float dt = 1.0/SAMPLE_RATE;
    float alpha = dt/(RC+dt);
    float filteredValue = sample;
    if (mAudioWave->size()>1) {
        filteredValue = mAudioWave->at(mAudioWave->size()-1) + (alpha*(filteredValue - mAudioWave->at(mAudioWave->size()-1)));
    }
    return filteredValue;
}

float GranularSyntheziser::echo(std::deque <float>* mAudioWave,float sample, float delay, float decay ){
    int delaySamples = (int)((float)delay*44.1f);
    float returnSample = sample;
    if (mAudioWave->size()>=delaySamples) {
        returnSample += decay*mAudioWave->at(mAudioWave->size()-delaySamples);
    }
    return returnSample;
}



bool GranularSyntheziser::loadWave(std::string path){
    std::ifstream myfile(path);
    if (myfile.is_open())
    {
        int sample = 0;
        u_char ubyte;
        unsigned char lbyte;
        int  i =0;
        while ( myfile.read(reinterpret_cast<char*>(&lbyte), 1))
        {
            if (i%2 == 0) {//upper
                sample = (short) (lbyte);
            }
            else{
                sample+= (short)(lbyte<<8);
                //mAudioWave.push_back((sample));
                music->push_back((float)(sample)/(float)INT16_MAX);
            }
            i++;
        }
        myfile.close();
        return true;
    }
    else {
        std::cout << "Unable to open file";
        return false;
    }
}

void GranularSyntheziser::setDecay(float decay){
    if (decay >= 0.0f && decay <= 1.0f) {
        mDecay = decay;
    }
}

float GranularSyntheziser::getDecay(){
    return mDecay;
}

void GranularSyntheziser::setDelay(float delay){
    mDelay = delay;
}

float GranularSyntheziser::getDelay(){
    return mDelay;
}

int GranularSyntheziser::getDuration(){
    return mDuration;
}

void GranularSyntheziser::setDuration(int duration){
    if(duration>0){
        mDuration = duration;
    }
}

int GranularSyntheziser::getOverlap(){
    return mOverlap;
}

void GranularSyntheziser::setBlank(int blank){
    mBlank = blank;
}

void GranularSyntheziser::setOverlap(int overlap){
    mOverlap = overlap;
}

float GranularSyntheziser::getVolume(){
    return mVolume;
}

void GranularSyntheziser::setVolume(float volume){
    mVolume = volume;
}

void GranularSyntheziser::setInitPosition(int initPos){
    //std::cout<<initPos<<std::endl;
    mInitPos = initPos;
}
int GranularSyntheziser::getInitPosition(){
    return mInitPos;
}