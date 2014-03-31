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
    mGrid = g;
    Chromosome* c = new Chromosome(g);
    if (isRandom){
        c->generateRandom();
    }
    mChromosomes.push_back(c);
}


void Genetic::evaluateAndEvolve(){
    while (mChromosomes.back()->getRate() != 100) {
        mGrid->setCoeffs(mChromosomes.back()->getCoeffs());
        mChromosomes.back()->rate();
        for(int i=0;i<mChromosomes.size();i++){
            for(int j=0;j<i;j++){
                if(mChromosomes[i]->getRate() > mChromosomes[j]->getRate()){
                    std::swap(mChromosomes[i],mChromosomes[j]);
                }
            }
        }
        Chromosome* mateChrom = getAParent();
        Chromosome* C = mChromosomes.back()->mate(mateChrom);
        mChromosomes.push_back(C);
        //std::cout<< getBest()->getRate() <<std::endl;
        printRates();
        //delete mateChrom;
    }
}


void Genetic::printRates(){
    for (int i = 0 ; i<mChromosomes.size(); i++) {
        std::cout<<mChromosomes[i]->getRate() << " -- ";
    }
    std::cout << std::endl;
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

Chromosome* Genetic::getAParent(){
    Chromosome* c = new Chromosome(mGrid);
    c->generateRandom();
    if (mChromosomes.size() <3) {
        return c;
    }
    else {
        Chromosome* p1 = getBest()->mate(c);
        c->generateRandom();
        Chromosome* p2 = mChromosomes[1]->mate(c);
        return p1->mate(p2);
    }
}
