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
#include <gecode/int.hh>
#include <gecode/minimodel.hh>

class Constrain{
public:
    Constrain(std::vector<float>* inputsValues, std::vector<float>* outputsValues);
    std::vector<float>* mInputsValues;
    std::vector<float>* mOutputsValues;
private:

    //float mOutputsValue;
};


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
    bool isCorrectSolution(boost::numeric::ublas::vector<float> solution);
    Grid* mGrid;
    std::vector<Constrain*> mListContrain;


};

#endif /* defined(__LibLoAndCap__ConstrainGenetic__) */
