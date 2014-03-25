//
//  Genetic.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 21/03/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "Genetic.h"
#include <cmath>

const int TOURNAMENT_SIZE = 3;

Genetic::Genetic (Grid* g, bool isRandom, float crossoverRatio, float elitismRatio, float mutationRatio, int size){
    srand(time(NULL));
    mCrossover = crossoverRatio;
    mElitism = elitismRatio;
    mMutation = mutationRatio;
    mSizePop = size;
    for (int i = 0; i < mSizePop; ++i) {
        Chromosome* c =new Chromosome(g);
        c->generateRandom();
        mChromosomes.push_back( c);
    }
}

void Genetic::evalPop(){
    for (int i = 0; i < mSizePop; ++i) {
        mChromosomes[i]->rate();
    }
    for(int i=0;i<mSizePop;i++){
        for(int j=0;j<i;j++){
            if(*mChromosomes[i]>*mChromosomes[j]){
                std::swap(mChromosomes[i],mChromosomes[j]);
            }
        }
    }
}

void Genetic::evolve(){
    Chromosome** temp = new Chromosome*[mSizePop];

    int cur = (int)ceil(mSizePop * mElitism);
    for(int i = 0; i < cur; ++i){
        temp[i] = new Chromosome(mChromosomes[i]->getCoeffs(),mChromosomes[i]->getSize());
    }

    while(cur<mSizePop){
        if ((rand()%100) <= mCrossover*100) {
            Chromosome** parents = this->selectParents();
            Chromosome** children = parents[0]->mate(parents[1]);

            if ((rand()%RAND_MAX) <= mMutation) {
                temp[cur++] = children[0]->mutate();
            } else {
                temp[cur++] = new Chromosome (children[0]->getCoeffs(),children[0]->getSize());
            }

            if (cur < mSizePop) {
                if ((rand()%RAND_MAX) <= mMutation) {
                    temp[cur] = children[1]->mutate();
                } else {
                    temp[cur] = children[1];
                }
            }
        }
        else{
            if ((rand()%100) <= mMutation*100) {
                temp[cur] = mChromosomes[cur]->mutate();
            } else {
                temp[cur] = new Chromosome(mChromosomes[cur]->getCoeffs(), mChromosomes[cur]->getSize());
            }
        }
        ++cur;
    }
    for(int i = 0; i < mSizePop; ++i){
        mChromosomes.clear();
        mChromosomes.push_back(temp[i]);
    }
    //delete[] temp;
}

Chromosome** Genetic::selectParents(){
    Chromosome** parents = new Chromosome*[2];
    for (int i = 0; i < 2; ++i) {
        parents[i] = mChromosomes[rand() % (mSizePop-1)];
        for (int j = 0; j < TOURNAMENT_SIZE; j++) {
            int cur = rand() % (mSizePop-1);
            if (*mChromosomes[cur] < *parents[i]) {
                parents[i] = mChromosomes[cur];
            }
        }
    }
    return parents;

}

Chromosome* Genetic::getBest(){
    return mChromosomes[0];

}