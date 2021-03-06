//
//  ScalingProcessing.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 14/01/15.
//  Copyright (c) 2015 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__ScalingProcessing__
#define __LibLoAndCap__ScalingProcessing__

#include <stdio.h>
#include "Processings.h"
#include "Grid.h"
#include <vector>

template<class T> class ScalingProcessing : public Processings{
public:
    ScalingProcessing(Grid* g, std::vector<T>* data, std::string name){
        T min = getMin(data);
        T max = getMax(data);
        g->addInput(name.c_str(), (float)min, (float)max, -1, 0, Converter::LINEAR);

        mOutput = g->getInputWithName(name.c_str());
        std::cout<< name << "min " <<min << " max " <<max <<std::endl;
    }
    //template<typename T>
    void process (T t){
        mOutput->setValue(t);
    }

    T getMin(std::vector<T>* data){
        T currentMin = data->at(0);
        for(int i = 1; i< data->size(); i++){
            if(data->at(i) < currentMin){
                currentMin  = data->at(i);
            }
        }
        return currentMin;
    }
    T getMax(std::vector<T>* data){
        T currentMax = data->at(0);
        for(int i = 1; i< data->size(); i++){
            if(data->at(i) > currentMax){
                currentMax  = data->at(i);
            }
        }
        return currentMax;
    }
    //template<typename T>
    void process (void* vdata){
        process(*((T*)vdata));
    }
    void setActive(bool active){
        mActive = active;
    }
private:
    void setSetter(int nbrSetter,...){

    }

    Setter<float>* mOutput;
};

#endif /* defined(__LibLoAndCap__ScalingProcessing__) */
