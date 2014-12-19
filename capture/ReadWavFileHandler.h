#ifndef fftproc_Readwavfile_h
#define fftproc_Readwavfile_h


#include <iostream>
#include <vector>
#include "FftProcessing.h"  
#include <pthread.h>
#include "CaptureDevice.h"
#include "Grid.h"


class ReadWavFileHandler : public CaptureDevice {
    
    
public:
    
    ReadWavFileHandler(Grid* g,std::string filePath);
    ~ReadWavFileHandler();
    
    void init();
    static void* callWavProcess(void* arg);
    void* WavProcess();

    
    
private:
    struct wave_header {
        char riff[4];
        uint_least32_t size;
        char wave[4];
        char fmt[4];
        uint_least32_t length;
        uint_least16_t encoding;
        uint_least16_t channels;
        uint_least32_t frequency;
        uint_least32_t byterate;
        uint_least16_t block_align;
        uint_least16_t bits_per_samples;
        char data[4];
        uint_least32_t data_size;
        int NumSamples;
    } wh;

    float* mSound;
    FILE *fp;
    bool loadWave(std::string filePath);
    FFTprocessing* fft;
    Grid* mGrid;
  
};

#endif
