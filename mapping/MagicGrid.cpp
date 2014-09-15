//
//  MagicGrid.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 8/09/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "MagicGrid.h"

using namespace Gecode;


MagicGrid::MagicGrid(bool share, MagicGrid& s) : Script(share,s), n(s.n), m(s.m), t(s.t) {
    gridMag.update(*this, share, s.gridMag);
}

MagicGrid::MagicGrid(const MagicGrid& magicGrid): //, const SizeOptions& optOutput
n(magicGrid.n),
m(magicGrid.m),
t(magicGrid.t),
gridMag(*this,n,-1.0,1.0)
{
    mConstrains = magicGrid.mConstrains;
    Matrix<FloatVarArray> TheMatrix(gridMag, m, n);
    //BoolExpr* e = new BoolExpr [mConstrains->size()];
    //for (int i = 0; i<m; i++) {
    for (int k = 0;k<mConstrains->size();k++){
        LinFloatExpr ligne;
        float outputValue = mConstrains->at(k)->mOutputsValues->at(0);
        for (int j=0; j<n; j++) {
            ligne = ligne + mConstrains->at(k)->mOutputsValues->at(j) * TheMatrix(0,j);
        }
        BoolExpr e = (ligne == 0.3);
        rel(*this,  e);
    }

    //}

    //rel(*this,  e);
    //rel(*this, 0.24 *  TheMatrix(0,0) +    TheMatrix(0,1) * 0.8 +      0.24 * TheMatrix(0,2) +     0.24 * TheMatrix(0,3)   == 0.9 );
    branch(*this, gridMag, FLOAT_VAR_SIZE_MIN(), FLOAT_VAL_SPLIT_MIN());


}


MagicGrid::MagicGrid(const GrilleOptions& opt): //, const SizeOptions& optOutput
            n(opt.InputLength()),
            m(opt.OutputLength()),
            t(opt.Constrains()->size()),
            gridMag(*this,n*m,-1.0,1.0)
{
    std::cout<<"NBR CONSTRAINS : " << opt.Constrains()->size() << std::endl;
    mConstrains = opt.Constrains();

    Matrix<FloatVarArray> TheMatrix(gridMag, m, n);
    //BoolExpr* e = new BoolExpr [mConstrains->size()];
    //for (int i = 0; i<m; i++) {
    int size = mConstrains->at(0)->mInputsValues->size();
    for (int k = 0;k<mConstrains->size();k++){
        LinFloatExpr* ligne = new LinFloatExpr(mConstrains->at(k)->mInputsValues->at(size - mConstrains->size()-1) * TheMatrix(0,0));
        float outputValue = mConstrains->at(k)->mOutputsValues->at(0);
        for (int j=1; j<n; j++) {
            int size = mConstrains->at(k)->mInputsValues->size();
            //std::cout<<"PARCOURS : " << j << std::endl;
            *ligne = *ligne + mConstrains->at(k)->mInputsValues->at(size - mConstrains->size() -2 + j) * TheMatrix(0,j);
        }
      //  std::cout<< (*ligne == 0.3) <<std::endl;
        BoolExpr* e = new BoolExpr(*ligne == 0.4 +(k*0.4));
        //*e = (ligne == 0.3);
        rel(*this,  *e);
    }

    //}

    //rel(*this,  e);
    //rel(*this, 0.24 *  TheMatrix(0,0) +    TheMatrix(0,1) * 0.8 +      0.24 * TheMatrix(0,2) +     0.24 * TheMatrix(0,3)   == 0.9 );
    branch(*this, gridMag, FLOAT_VAR_SIZE_MIN(), FLOAT_VAL_SPLIT_MAX());
    //
     /*for (int i = 0; i < n; i++) {
        Gecode::linear(*this, m.col(i), FRT_EQ, s);
     }*/



    // Gecode::branch(*this, gridMag, FLOAT_VAR_SIZE_MIN(), FLOAT_VAR_SIZE_MIN());
}


Gecode::Space* MagicGrid::copy(bool share) {
    return new MagicGrid(share,*this);
}

void MagicGrid::print(std::ostream& os) const {
    // Pour acceder au tableau comme à une matrice
    Matrix<FloatVarArray> TheMatrix(gridMag, m, n);
     for (int i = 0; i < m; i++) {
         os << "\t";
         for (int j = 0; j < n; j++) {
             os.width(2);
             os << TheMatrix(i,j) << "\t";
         }
         os << std::endl;
     }
}


