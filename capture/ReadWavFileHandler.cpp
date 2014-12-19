#include "ReadWavFileHandler.h"


pthread_t thread;

ReadWavFileHandler::ReadWavFileHandler(Grid*g, std::string filePath){
    loadWave(filePath);
    mProcessings.push_back(new FFTprocessing (g, wh.frequency, 1024));
    mGrid = g;
}

ReadWavFileHandler::~ReadWavFileHandler(){

}

void ReadWavFileHandler::init(){
    int result;
    

    result=pthread_create(&thread,NULL,ReadWavFileHandler::callWavProcess,this);
    //pthread_exit(&thread);
    }

void* ReadWavFileHandler::callWavProcess(void *arg){
    return ((ReadWavFileHandler*)arg)->WavProcess();
    
}

bool ReadWavFileHandler::loadWave(std::string filePath){
    fp = fopen(filePath.c_str(),"rb");
    if (fp == NULL){
        std::cout<<"path fichier faux"<<std::endl;
        return false;
    }
    fread(wh.riff, 4, 1, fp);
    fread(&wh.size, 4, 1, fp);
    fread(wh.wave,  4, 1, fp);
    fread(wh.fmt, 4  , 1, fp);
    fread(&wh.length, 4,1,fp);
    fread(&wh.encoding, 2,1,fp);
    fread(&wh.channels, 2,1,fp);
    fread(&wh.frequency, 4,1,fp);
    fread(&wh.byterate, 4,1,fp);
    fread(&wh.block_align, 2,1,fp);
    fread(&wh.bits_per_samples, 2,1,fp);
    fread(wh.data, 4, 1, fp);
    fread(&wh.data_size,4,1,fp);
    wh.NumSamples= ((wh.data_size*8)/wh.bits_per_samples)/wh.channels;
    mSound = new float[wh.NumSamples];
    int count = 0;

    short int b = 0;
    while(count <wh.NumSamples){
        fread(&b,1,2,fp);
        mSound[count]= (b/(float)INT16_MAX);
        if(wh.channels==2){
            fread(&b,1,2,fp);
        }

        count++;
    }
    return true;
}

void* ReadWavFileHandler::WavProcess(){
    int N=1024,N0=0;

    clock_t t1,t2;

    t1= clock();

    for (int i = 0 ; i<wh.NumSamples; i+=N) {
        std::vector<Processings*>::iterator it = mProcessings.begin();
        for (it= mProcessings.begin(); it!=mProcessings.end();i++ ) {
            (*it)->process(mSound+i);
        }
        //fft->process(mSound+i);
        mGrid->compute();
        float sc=(float)N/(float)wh.frequency;
        t2 = clock();
        float t=(t2 - t1)/(double) CLOCKS_PER_SEC;
        if (t >= sc){
            t1 = t2;
        }else{
            usleep((unsigned int)((sc  - t)*1000000));
            t1= clock();
        }
        
        N0+=N;

    }
    WavProcess();

    return 0;
    
}

