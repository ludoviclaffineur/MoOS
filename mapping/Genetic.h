//
//  Genetic.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 21/03/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__Genetic__
#define __LibLoAndCap__Genetic__

#include <iostream>
#include "Grid.h"
#include "Chromosome.h"


class Genetic {
public:
    Genetic (Grid* g, bool isRandom, float crossoverRatio, float elitismRatio, float mutationRatio, int size);
    void evalPop();
    void evolve();
    Chromosome** selectParents();
    Chromosome* getBest();

    float getElitism(){
		return mElitism;
	}
    void setElitism(float elit){
		mElitism = elit;
	}
    float getMutation(){
		return mMutation;
	}

	void setMutation(float mut){
		mMutation = mut;
	}

	float getCrossover(){
		return mCrossover;
	}

	void setCrossover(float cross){
		mCrossover = cross;
	}

	int getSizePop(){
		return mSizePop;
	}

	void setSizePop(int sizep){
		mSizePop = sizep;
	}


private:
    std::vector<Chromosome*> mChromosomes;
	float   mElitism;
	float   mMutation;
	float   mCrossover;
	int     mSizePop;
};

#endif /* defined(__LibLoAndCap__Genetic__) */
