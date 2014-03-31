//
//  Chromosome.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 21/03/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__Chromosome__
#define __LibLoAndCap__Chromosome__

#include <iostream>
#include "Grid.h"


class Chromosome{
public:
    Chromosome();
    Chromosome (Grid* g);
    Chromosome(float* coeffs, long int size);
    void rate();
    Chromosome* mate(Chromosome* c);
    Chromosome* mutate();
    void generateRandom();
    Grid* getGrid();
    void setGene(Grid* g);
    void setRate(int rate);
    int getRate();
    float* getCoeffs();
    void setCoeffs(float* coeffs, long int size);
    long int getSize(){
        return mSize;
    }



    bool operator==(Chromosome c2) const;
    bool operator!=(Chromosome c2) const;
    bool operator<(Chromosome c2) const;
    bool operator>(Chromosome c2) const;
    void operator=(Chromosome c2);

private:
    int     mRate;
    long int   mSize;
    float*  mCoeffs;
};

#endif /* defined(__LibLoAndCap__Chromosome__) */
