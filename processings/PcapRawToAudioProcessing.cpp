//
//  PcapRowToAudioProcessing.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 25/03/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "PcapRawToAudioProcessing.h"

#include <stdio.h>
#include <math.h>
#include "portaudio.h"
#define NUM_SECONDS   (40)
#define SAMPLE_RATE   (44100)




 int patestCallback( const void *inputBuffer, void *outputBuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo* timeInfo,
                          PaStreamCallbackFlags statusFlags,
                          void *userData )
{
    /* Cast data passed through stream to our structure. */
    PcapRawToAudioProcessing* ptr = (PcapRawToAudioProcessing*) userData;
     //paTestData *data = (paTestData*)userData;
    //std::vector <float>* mu =  ( std::vector <float>*) userData;
    float *out = (float*)outputBuffer;
    unsigned int i;
    (void) inputBuffer; /* Prevent unused variable warning. */
    static int parcour = 0;
    for( i=0; i<framesPerBuffer; i++ )
    {

        //*out++ = data->left_phase;  /* left */
        //*out++ = data->right_phase;  /* right */

        *out++ = (float) ptr->data->left_phase;
        *out++ = (float) ptr->data->right_phase;


        //std::cout<< ptr->music->at(parcour) <<std::endl;
        if(parcour >= ptr->music->size()){
            ptr->data->left_phase = 0;
        }
        else{
            ptr->data->left_phase = ptr->music->at(parcour++);
        }
          /* left */


        //ptr->data->right_phase = ptr->music->at(parcour++);  /* right */
        //parcour++;
        //std::cout<< "Elements: "<<  << std::endl ;


        //float sampleFromeFile = *ptr->music.begin();

       // ptr->data->right_phase = sampleFromeFile;
       // ptr->data->left_phase = sampleFromeFile;

       //data->right_phase = 1.0-(rand()%200/200.0) ;
       //data->left_phase = 1.0-(rand()%200/200.0);


        //ptr->music->erase(ptr->music->begin());
        /* Generate simple sawtooth phaser that ranges between -1.0 and 1.0. */
        //data->left_phase += 0.01f;
        /* When signal reaches top, drop back down. */
        //if( data->left_phase >= 1.0f ) data->left_phase -= 2.0f;
        /* higher pitch so we can distinguish left and right. */
        //data->right_phase += 0.03f;
        //if( data->right_phase >= 1.0f ) data->right_phase -= 2.0f;
    }
    return 0;
}

//static paTestData data;
PcapRawToAudioProcessing::PcapRawToAudioProcessing(){
    PaStream *stream;
    PaError err;
    std::ifstream file(s, std::ifstream::in);
    music = new std::vector <float>();
    //char byte;
   /* while (file.good()) {
        byte = file.get();
        double a =((float)byte/128.0f);
        music->push_back(a);
        //printf(" %f ", (float)byte);
    }*/


    data = new paTestData;

    printf("PortAudio Test: output sawtooth wave.\n");
    /* Initialize our data for use by callback. */
    data->left_phase = data->right_phase = 0.0;
    /* Initialize library before making any other calls. */
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

void PcapRawToAudioProcessing::process(const u_char *data){
    int i = 0;
    while (*data != '\0') {
        int32_t* a  = (int32_t*) data;
        data += 4;
       //std::cout<< (float)(*a)/INT32_MAX << std::endl;
        music->push_back((float)(*a)/INT32_MAX);


        //std::cout<< bitCount(data)<< std::endl;
    }
}


unsigned int PcapRawToAudioProcessing::bitCount (const u_char* value) {
    unsigned int count = 0;
    for (int i =0 ;i<sizeof(value);i++){
        u_int8_t* IValue = (u_int8_t*) value;
        while (IValue > 0) {           // until all bits are zero
            if ((*IValue & 1) == 1)     // check lower bit
                count++;
            *IValue >>= 1;              // shift bits, removing lower bit
        }
        value++;
    }

    return count;
}


void PcapRawToAudioProcessing::setActive(bool active){

}


PcapRawToAudioProcessing::~PcapRawToAudioProcessing(){
    err = Pa_StopStream( stream );
    err = Pa_CloseStream( stream );
    Pa_Terminate();
    printf("Test finished.\n");
}