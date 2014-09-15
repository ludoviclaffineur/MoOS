//
//  MagicGrid.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 8/09/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__MagicGrid__
#define __LibLoAndCap__MagicGrid__

#include <iostream>
#include <gecode/driver.hh>
#include <gecode/float.hh>
#include <gecode/minimodel.hh>
#include <vector>
#include "Constrain.h"
#include "GrilleOptions.h"

using namespace Gecode;
class MagicGrid : public Gecode::Script{

public:
    MagicGrid(const GrilleOptions& opt);
    MagicGrid(const MagicGrid& magicGrid);
    MagicGrid(bool share, MagicGrid& s);
    virtual Space* copy(bool share);
    virtual void print(std::ostream& os) const;
    //virtual const int restart() const;
private:
    const int n; //inputs
    const int m; //outputs
    const int t; //nbr contrain
    std::vector<IA::Constrain*>* mConstrains;
    FloatVarArray gridMag;
};
#endif /* defined(__LibLoAndCap__MagicGrid__) */
