#include "ReadWavFileHandler.h"
#include <cstring>


pthread_t thread;

ReadWavFileHandler::ReadWavFileHandler(Grid*g, std::string filePath){
    mSound = NULL;
    mLoaded = loadWave(filePath);
    if (!mLoaded) {
        // Valeurs sûres : l'input FFT est créé mais aucun thread de lecture ne démarre
        std::cerr << "ReadWavFileHandler : impossible de lire " << filePath << std::endl;
        wh.frequency = 44100;
        wh.NumSamples = 0;
    }
    mProcessings.push_back(new FFTprocessing (g, wh.frequency, 1024));
    mGrid = g;
}

ReadWavFileHandler::~ReadWavFileHandler(){

}

void ReadWavFileHandler::init(){
    if (!mLoaded) {
        return;
    }
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
    // Seul le WAV PCM 16 bits mono/stéréo à en-tête canonique (44 octets) est géré
    if (memcmp(wh.riff, "RIFF", 4) != 0 || memcmp(wh.wave, "WAVE", 4) != 0 || memcmp(wh.data, "data", 4) != 0
        || wh.bits_per_samples != 16 || (wh.channels != 1 && wh.channels != 2) || wh.frequency == 0) {
        std::cout<<"format WAV non supporte (PCM 16 bits mono/stereo attendu)"<<std::endl;
        fclose(fp);
        return false;
    }
    wh.NumSamples= ((wh.data_size*8)/wh.bits_per_samples)/wh.channels;
    if (wh.NumSamples < 1024) {
        std::cout<<"fichier WAV trop court (moins d'une fenetre de 1024 echantillons)"<<std::endl;
        fclose(fp);
        return false;
    }
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
    fclose(fp);
    return true;
}

void* ReadWavFileHandler::WavProcess(){
    int N=1024,N0=0;

    clock_t t1,t2;

    t1= clock();

    // Lecture en boucle du fichier (auparavant par récursion, qui faisait grossir la pile)
    while (true) {
    for (int i = 0 ; i + N <= wh.NumSamples; i+=N) {
        float* window = mSound+i;
        std::vector<Processings*>::iterator it = mProcessings.begin();
        for (it= mProcessings.begin(); it!=mProcessings.end();it++ ) {
            // Processings::process(void*) attend un float** (cf. FFTprocessing::process)
            (*it)->process(&window);
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
    }

    return 0;
    
}

