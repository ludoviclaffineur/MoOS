//
//  GrilleOptions.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 9/09/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__GrilleOptions__
#define __LibLoAndCap__GrilleOptions__

#include <iostream>
#include <gecode/driver.hh>

#include <gecode/float.hh>
#include <gecode/minimodel.hh>
#include "Constrain.h"
using namespace Gecode;

class GrilleOptions : public SizeOptions {
private:
    /// Max slack parameter
    Driver::UnsignedIntOption _InputLength;
    Driver::UnsignedIntOption _OutputLength;
    std::vector<IA::Constrain*>* _Constrains;
    //Driver::UnsignedIntOption _maxstall;

public:
    /// Initialize options for example with name \a s
    GrilleOptions(const char* s, int nbrInputs, int nbrOutputs, std::vector <IA::Constrain*>* lConstrains)
    : SizeOptions(s),
    _InputLength("InputLength", "Maximum numbere of stalls", nbrInputs),
    _OutputLength("InputLength", "Maximum numbere of stalls", nbrOutputs)
    {
        // Add options
        _Constrains = lConstrains;
        add(_InputLength);
        add(_OutputLength);
    }
    /// Parse options from arguments \a argv (number is \a argc)
    void parse(int& argc, char* argv[]) {
        SizeOptions::parse(argc,argv);
    }
    /// Get max stalls
    int OutputLength(void) const { return _OutputLength.value(); }
    int InputLength(void) const { return _InputLength.value(); }
    std::vector<IA::Constrain*>* Constrains(void) const { return _Constrains; }
};

#endif /* defined(__LibLoAndCap__GrilleOptions__) */
