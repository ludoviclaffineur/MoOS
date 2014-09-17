//
//  ConstrainGenetic.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 9/05/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "ConstrainGenetic.h"



ConstrainGenetic::ConstrainGenetic(Grid* g){
    mGrid = g;
    mListContrain = new std::vector<IA::Constrain*> ();
    srand(time(NULL));
}

void ConstrainGenetic::setConstrain(std::vector<float> inputsValues, std::vector<float> outputsValues){
    //mListContrain.push_back(new Constrain(new std::vector<float>(inputsValues), new std::vector<float>(outputsValues)));
}

void ConstrainGenetic::setConstrain(){
    std::vector<float> input;
    std::vector<float> output;
    for (int i =0 ; i<mGrid->getOutputs()->size(); i++) {
        std::cout<< mGrid->getOutputs()->at(i)->getValue() << std::endl;
        output.push_back(mGrid->getOutputs()->at(i)->getValue());
    }
    
    for (int i=0; i<mGrid->getNbrInputs(); i++) {
        input.push_back(mGrid->getInputs()->at(i)->getValue());
        std::cout<<mGrid->getInputs()->at(i)->getValue()<< "\t";
    }
    std::cout<<std::endl;
    std::cout<<std::endl;
    mListContrain->push_back(new IA::Constrain(new std::vector<float>(input), new std::vector<float>(output)));
    if (mListContrain->size() ==2){
        computeGrid();
    }
}


bool ConstrainGenetic::invertMatrix(const boost::numeric::ublas::matrix<float>& input, boost::numeric::ublas::matrix<float>& inverse)
{
    using namespace boost::numeric::ublas;
    using namespace std;
    typedef permutation_matrix<std::size_t> pmatrix;

    // create a working copy of the input
    matrix<float> A(input);

    // create a permutation matrix for the LU-factorization
    pmatrix pm(A.size1());

    // perform LU-factorization
    int res = lu_factorize(A, pm);
    if (res != 0)
        return false;

    // create identity matrix of "inverse"
    inverse.assign(identity_matrix<float> (A.size1()));

    // backsubstitute to get the inverse
    lu_substitute(A, pm, inverse);

    return true;
}

void ConstrainGenetic::computeGridOld(){
    float** gridCoeff = new float*[mGrid->getNbrInputs()];
    for (int i =0 ; i<mGrid->getNbrInputs(); i++) {
        gridCoeff[i] = new float [mGrid->getNbrOutputs()];
    }
    for (int i = 0; i< mGrid->getNbrInputs()- mListContrain->size(); i++) {
        gridCoeff[i][0] = ((1000-rand()%2000)/1000.0);
    }

    for (int k = 0; k<mListContrain->size(); k++) {
        float coefDotInput =0.0;
        for (int i = 0; i< mGrid->getNbrInputs()- mListContrain->size() -2 ; i++) {
            coefDotInput += gridCoeff[i][0]* (mListContrain->at(k)->mInputsValues->at(i));
        //printf("%f ", gridCoeff[i][j]);
        //printf("Input value %f ", mListContrain.at(0)->mInputsValues->at(i));
        }
    }
    //GrilleOptions opt("options Grilles",mListContrain->size() +2 ,mGrid->getNbrOutputs(),mListContrain);

    //Gecode::Script::run<MagicGrid,DFS,GrilleOptions>(opt);
}






void ConstrainGenetic::computeGrid(){
    using namespace boost::numeric::ublas;
    //using namespace std;
    for (int j = 0; j< mListContrain->size() ; j++) {
        for (int i = 0; i< mGrid->getNbrInputs() ; i++) {
            std::cout<<mListContrain->at(j)->mInputsValues->at(i) << "\t";
        }
        std::cout<<std::endl;
    }


    float** gridCoeff = new float*[mGrid->getNbrInputs()];
    for (int i =0 ; i<mGrid->getNbrInputs(); i++) {
        gridCoeff[i] = new float [mGrid->getNbrOutputs()];
    }


    matrix<float> coeffMatrix (mListContrain->size(),mListContrain->size());
    for (int i = 0; i<mListContrain->size(); i++) {
        for (int j = 0; j<mListContrain->size(); j++){
            coeffMatrix(i,j)= mListContrain->at(i)->mInputsValues->at(mGrid->getNbrInputs()-mListContrain->size()+j);
        }
    }

    vector<float> appartConstance (mListContrain->size());
    vector<float> solution (mListContrain->size());

    for (int j = 0; j<mGrid->getNbrOutputs(); j++) {
        do{
            float coefDotInput = 0.0;
            for (int i = 0; i< mGrid->getNbrInputs()- mListContrain->size(); i++) {
                gridCoeff[i][j] = ((1000-rand()%2000)/1000.0);
            }
            for (int k = 0; k<mListContrain->size(); k++) {


                coefDotInput =0.0;
                 for (int i = 0; i< mGrid->getNbrInputs()- mListContrain->size(); i++) {
                    coefDotInput += gridCoeff[i][j]* (mListContrain->at(k)->mInputsValues->at(i));
                    //printf("%f ", gridCoeff[i][j]);
                    //printf("Input value %f ", mListContrain.at(0)->mInputsValues->at(i));
                }

                appartConstance(k) = mListContrain->at(k)->mOutputsValues->at(j) - coefDotInput;
                //std::cout<< coeffMatrix << std::endl << appartConstance << std::endl;
                matrix<float> reverse(mListContrain->size(), mListContrain->size());

                // coefDotInput+= gridCoeff[mGrid->getNbrInputs()-1][j] *mListContrain.at(0)->mInputsValues->size()-1
                if (invertMatrix(coeffMatrix, reverse)) {
                    solution =  prod <vector<float>>(reverse, appartConstance);
                    //std::cout<<"Coeff de base"<< coeffMatrix<< std::endl << "matrice reverse" << reverse << std::endl << "inv*base" << prod(reverse, coeffMatrix) << std::endl << "Solution " <<solution << std::endl;

                }

                //printf("\n coeff input %f \n", coefDotInput);


                //printf("\n last grid element %f \n",  gridCoeff[mGrid->getNbrInputs()-1][j]);
                
            }
            
            
            
        }
        while (!isCorrectSolution(solution) );
        std::cout<<"Output Résolu: " << j << std::endl;
        for (int i =0 ; i<solution.size() ; i++){
            gridCoeff[mGrid->getNbrInputs() - mListContrain->size()+i][j] = solution(i);
        }
    }

    std::cout<< "FINISHED" <<std::endl;
   /* std::cout<< coeffMatrix << std::endl << appartConstance << std::endl;
    matrix<float> reverse(mListContrain.size(), mListContrain.size());

   // coefDotInput+= gridCoeff[mGrid->getNbrInputs()-1][j] *mListContrain.at(0)->mInputsValues->size()-1
    if (invertMatrix(coeffMatrix, reverse)) {
        vector<float> solution (mListContrain.size());
        solution =  prod <vector<float>>(reverse, appartConstance);
        std::cout<<"Coeff de base"<< coeffMatrix<< std::endl << "matrice reverse" << reverse << std::endl << "inv*base" << prod(reverse, coeffMatrix) << std::endl << "Solution " <<solution << std::endl;

    }*/
    for (int k = 0; k<mListContrain->size(); k++) {

        for (int j = 0; j<mGrid->getNbrOutputs(); j++) {
            float testOutput = 0.0;
            for (int i = 0; i< mGrid->getNbrInputs(); i++) {
                //gridCoeff[i][j] = ((1000-rand()%2000)/1000.0);
                testOutput += gridCoeff[i][j]* (mListContrain->at(k)->mInputsValues->at(i));
                //printf("%f ", gridCoeff[i][j]);
            }
            printf("\n Check Input input %f \n", testOutput);
            //gridCoeff[mGrid->getNbrInputs()-1][j] = (mListContrain.at(0)->mOutputsValue - coefDotInput)/ (*(mListContrain.at(0)->mInputsValues->end()));
            //
        }
    }
    mGrid->setCoeffs(gridCoeff);

}


bool ConstrainGenetic::isCorrectSolution(boost::numeric::ublas::vector<float> solution){
    for (int i=0;i<solution.size(); i++){
        if (solution(i)>1 || solution(i)<-1)
            return false;

    }
    return true;
}


/*Constrain class*/


