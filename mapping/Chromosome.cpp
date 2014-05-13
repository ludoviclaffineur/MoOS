//
//  Chromosome.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 21/03/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "Chromosome.h"

Chromosome::Chromosome(){

}

Chromosome::Chromosome(Grid* g){
    mRate = -1;
    mCoeffs = g->getCoeffs();
    mSize = g->getCells()->size();
    mNbrInputs = g->getInputs()->size();
}

Chromosome::Chromosome(float* coeffs, long int size){
    mCoeffs = new float[size];
    setCoeffs(coeffs, size);
    mSize = size;
    mRate = -1;
}

void Chromosome::rate(){
    std::cout << "Grid: ";
    for(int i = 0; i < mSize ; ++i){
         std::cout  << mCoeffs[i] << " - ";
    }
    int i;
    std::string buf;
    bool good;
    std::cout << "Cela vous convient-il (note entre 0 et 100)? " <<std::flush;
    do {
        good = false;
        if (!std::cin)
            std::cin.clear();
        std::cin.putback(';');
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), ';');
        std::cin >> buf;
        buf.append("\n");
        std::istringstream iss(buf);
        iss >> i;
        if (iss.get() == '\n')
            good = iss.good();
    } while (!good || i < 0 || i > 100);
    mRate = i;
    std::cout << "le poid defini: " << mRate << std::endl;
}

float* Chromosome::getCoeffs(){
    return mCoeffs;
}

Chromosome* Chromosome::mutate(){
    float* gmut = new float[mSize];
    for(int i = 0; i < mSize ; ++i){
        gmut[i] = mCoeffs[i];
    }
    srand(time(NULL));
    int pos = rand()%3;
    int newval = rand() % 101;
    gmut[pos] = (float)newval/100;
    Chromosome* ret = new Chromosome(gmut,mSize);
    return ret;
}

Chromosome* Chromosome::mate(Chromosome* random){
    float* newCoeffs = new float[mSize];
    float* randomCoeffs = random->getCoeffs();
    for(int i=0 ; i<mSize ; i++){
        newCoeffs[i] = ((mCoeffs[i]*(float)mRate) + randomCoeffs[i]*(100.0-(float)mRate))/100.0;
    }
    return (new Chromosome ( newCoeffs, mSize));

}

void Chromosome::generateRandom(){
    for(int j = 0; j<mSize; ++j){
        mCoeffs[j] = (float)(50.0 - rand()%100) / (10.0*(float)mNbrInputs) ;
    }
}

void Chromosome::setGene(Grid* g){
    mCoeffs = g->getCoeffs();
    mSize = g->getCells()->size();
}

void Chromosome::setCoeffs(float* coeffs, long int size){
    if (!mCoeffs){
        mCoeffs = new float[size];
        mSize = size;
    }
    for (int i =0; i< size;i++){
        mCoeffs[i] = coeffs[i];
    }
}


void Chromosome::setRate(int rate){
    mRate = rate;
}

int Chromosome::getRate(){
    return mRate;
}

bool Chromosome::operator==(Chromosome c2) const{
    if (mRate == c2.getRate())
        return true;
    else return false;
}

bool Chromosome::operator!=(Chromosome c2) const{
    if (mRate != c2.getRate())
        return true;
    else return false;
}

bool Chromosome::operator<(Chromosome c2) const{
    if (mRate < c2.getRate())
        return true;
    else return false;
}

bool Chromosome::operator>(Chromosome c2) const{
    if (mRate > c2.getRate())
        return true;
    else return false;
}

void Chromosome::operator=(Chromosome c2){
    this->setCoeffs(c2.getCoeffs(), c2.mSize);
}

