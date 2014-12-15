//
//  GranularSyntheziser.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 12/12/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "GranularSyntheziser.h"
#include <fstream>
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

        ptr->data->left_phase = sample;
        ptr->data->right_phase = sample;


    }
    return 0;
}







GranularSyntheziser::GranularSyntheziser(Grid* g){
    PaStream *stream;
    PaError err;
    //mEnvelope = 0;
    //std::ifstream file(s, std::ifstream::in);
    music = new std::vector <float>();
    //char byte;
    /* while (file.good()) {
     byte = file.get();
     double a =((float)byte/128.0f);
     music->push_back(a);
     //printf(" %f ", (float)byte);
     }*/
    mOverlap = 3000.0f;
    mPosition = 0.0f;
    data = new paTestData;

    printf("PortAudio Test: output sawtooth wave.\n");
    /* Initialize our data for use by callback. */
    data->left_phase = data->right_phase = 0.0;
    /* Initialize library before making any other calls. */
    loadWave("/Users/ludoviclaffineur/Documents/LibLoAndCap/data/sound5.wav");

    mGrains.push_back(new Grain(music, 2000 ,500));
    mGrains.push_back(new Grain(music, 3000,500 ));
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
    if(mPosition++ > (*mGrains.end())->mDuration - mOverlap){
        mGrains.push_back(new Grain(music, 4000, 2000));
        mPosition = 0.0f;
    }

    if (mGrains.size()!=0) {
        if (mGrains[0]->isDone()){
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
int GranularSyntheziser::getDuration(){
    return mDuration;
}

void GranularSyntheziser::setDuration(int duration){
    mDuration = duration;
}

int GranularSyntheziser::getOverlap(){
    return mOverlap;
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