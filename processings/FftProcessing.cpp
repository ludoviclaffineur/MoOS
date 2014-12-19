//
//  FFTprocessing.cpp
//  fftproc
//
//  Created by Louis Commere on 21/11/14.
//  Copyright (c) 2014 Louis Commere. All rights reserved.
//

#include "FFTprocessing.h"
#include "Input.h"


FFTprocessing::FFTprocessing(float sampleRate, int windowsSize){
    mSampleRate = sampleRate;
    mWindowSize = windowsSize;
};

FFTprocessing::FFTprocessing(Grid* g, float sampleRate, int windowsSize){
    mSampleRate = sampleRate;
    mWindowSize = windowsSize;
    mFrequenciesAmplitudes = new Setter<float>*[windowsSize];
    for (int i = 0; i<windowsSize/2; i++) {
        std::stringstream name;
        name<< (int) (i*(sampleRate/(float)windowsSize));
        g->addInput(name.str().c_str(), 0, 1, -1, 0, Converter::LINEAR);
        mFrequenciesAmplitudes[i] = g->getInputWithName(name.str().c_str());
        std::cout<< (int)(i*(sampleRate/(float)windowsSize)) <<std::endl;
    }

};

void FFTprocessing::fft(float* b){
    
    unsigned long n,mmax,m,j,istep,i;
    double wtemp,wr,wpr,wpi,wi,theta,tempr,tempi;
    
    std::vector<float> t;
   
    
    for(float* it = b; it != b+mWindowSize;++it){
        t.push_back(*it);
        t.push_back(0);
    }
    
    // reverse-binary reindexing
    n=mWindowSize << 1;
	j=0;
	for (i=0;i<n;i+=2) {
		if (j > i) {
            std::swap(t[j],t[i]);
            std::swap(t[j+1],t[i+1]);
		}
		m=n >> 1;
		while (m >= 2 && j >= m) {
			j -= m;
			m >>= 1;
		}
		j += m;
	}
    //Danielson-Lanzcos routine
    
    mmax=2;
	while (n > mmax) {
		istep=mmax << 1;
		theta=-(2*M_PI/mmax);
		wtemp=sin(0.5*theta);
		wpr = -2.0*wtemp*wtemp;
		wpi=sin(theta);
		wr=1.0;
		wi=0.0;
		for (m=1;m<mmax;m+=2) {
			for (i=m;i<=n;i+=istep) {
				j=i+mmax;
				tempr=wr*t[j-1]-wi*t[j];
				tempi=wr*t[j]+wi*t[j-1];
				t[j-1]=t[i-1]-tempr;
				t[j]=t[i]-tempi;
				t[i-1] += tempr;
				t[i] += tempi;
			}
			wr=(wtemp=wr)*wpr-wi*wpi+wr;
			wi=wi*wpr+wtemp*wpi+wi;
		}
		mmax=istep;
	}
    for(int unsigned i=0;i<mWindowSize/2;i++){
        mFrequenciesAmplitudes[i]->setValue(sqrt(pow(t[2*i],2)+pow(t[2*i+1],2))/(float)mWindowSize);
        //sp.push_back(sqrt(pow(t[2*i],2)+pow(t[2*i+1],2))/(float)mWindowSize);
    }    
};

void  FFTprocessing::print(){
    for(int i=0;i<sp.size();i++){
        std::cout<<sp[i]<<"\t";
    }
    std::cout<<"\n\n\n"<<std::endl;
};


void::FFTprocessing::process(float* window){
    fft(window);
    //print();
    //sp.clear();
};



