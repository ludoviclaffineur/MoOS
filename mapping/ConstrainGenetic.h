//
//  ConstrainGenetic.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 9/05/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__ConstrainGenetic__
#define __LibLoAndCap__ConstrainGenetic__

#include <iostream>
#include "Grid.h"
#include "Input.h"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <gecode/driver.hh>
//#include "MagicGrid.h"
#include "Converter.h"
#include "GrilleOptions.h"



class ConstrainGenetic{
public:
    ConstrainGenetic(Grid* g);
    void setConstrain(std::vector<float> inputsValues, std::vector<float> outputsValues);
    void triangularMatrix();
    void computeGrid();
    void computeGridOld();
    void setConstrain();
    bool invertMatrix(const boost::numeric::ublas::matrix<float>& input, boost::numeric::ublas::matrix<float>& inverse);
   
private:
    bool isCorrectSolution(std::vector<float> solution);
    Grid* mGrid;
    std::vector<IA::Constrain*>* mListContrain;
    void printSystem(boost::numeric::ublas::matrix<float> A, std::vector<float> b);
    void printSolution(std::vector<float> x);
    std::vector<float> gauss (boost::numeric::ublas::matrix<float> input, std::vector<float>& x, std::vector<float> b);


};

#endif /* defined(__LibLoAndCap__ConstrainGenetic__) */
