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
        //std::cout<< mGrid->getOutputs()->at(i)->getValue() << std::endl;
        output.push_back(mGrid->getOutputs()->at(i)->getValue());
    }
    
    for (int i=0; i<mGrid->getNbrInputs(); i++) {
        input.push_back(mGrid->getInputs()->at(i)->getValue());
        std::cout<<mGrid->getInputs()->at(i)->getValue()<< "\t";
    }
    std::cout<<std::endl;
    //std::cout<<std::endl;
    mListContrain->push_back(new IA::Constrain(new std::vector<float>(input), new std::vector<float>(output)));
    if (mListContrain->size() ==3){
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


    float** gridCoeff = new float*[mGrid->getNbrInputs()];
    for (int i =0 ; i<mGrid->getNbrInputs(); i++) {
        gridCoeff[i] = new float [mGrid->getNbrOutputs()];
    }
    std::vector<int> MaxCurveIds;
    //find maximum of the input curve
    for (int i =0; i<mListContrain->size(); i++) {
        int max = 0;
        for (int j = 0; j< mListContrain->at(i)->mInputsValues->size(); j++){
            if (mListContrain->at(i)->mInputsValues->at(j)> mListContrain->at(i)->mInputsValues->at(max)) {
                max = j;
            }
            
        }
        MaxCurveIds.push_back(max);
    }



    matrix<float> coeffMatrix (mListContrain->size(),mListContrain->size());
    for (int i = 0; i<mListContrain->size(); i++) {
        for (int j = 0; j<mListContrain->size(); j++){
            coeffMatrix(i,j)= mListContrain->at(i)->mInputsValues->at(mGrid->getNbrInputs()-mListContrain->size()+j);
        }
    }

    std::vector<float> appartConstance (mListContrain->size());
    std::vector<float> solution (mListContrain->size());

    for (int j = 0; j<mGrid->getNbrOutputs(); j++) {


        do{
            solution.clear();

            float coefDotInput = 0.0;
            for (int i = 0; i< mGrid->getNbrInputs()- mListContrain->size(); i++) {
                gridCoeff[i][j] = ((1000-rand()%2000)/1000.0);
            }
             std::vector<float> outputsConstraint;
            outputsConstraint.clear();
            for (int k = 0; k<mListContrain->size(); k++) {
                solution.push_back(0.0);
                coefDotInput =0.0;
                 for (int i = 0; i< mGrid->getNbrInputs()- mListContrain->size(); i++) {
                    coefDotInput += gridCoeff[i][j]* (mListContrain->at(k)->mInputsValues->at(i));
                }
                appartConstance[k] = mListContrain->at(k)->mOutputsValues->at(j) - coefDotInput;
                outputsConstraint.push_back(mListContrain->at(k)->mOutputsValues->at(j));
                
            }
            solution = gauss(coeffMatrix, solution, appartConstance);
        }
        while (!isCorrectSolution(solution) );
        std::cout<<"Output Résolu: " << j << std::endl;
        for (int i =0 ; i<solution.size() ; i++){
            std::cout<<"Solution "<< solution[i] << std::endl;
            gridCoeff[mGrid->getNbrInputs() - mListContrain->size()+i][j] = solution[i];
        }
        printSolution(solution);
    }

    std::cout<< "Done" <<std::endl;
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


bool ConstrainGenetic::isCorrectSolution(std::vector<float> solution){
    for (int i=0;i<solution.size(); i++){
        if (solution[i]>1 || solution[i]<-1)
            return false;

    }
    return true;
}






/* Affichage du système */
void ConstrainGenetic::printSystem(boost::numeric::ublas::matrix<float> A, std::vector<float> b)
{
    int i , j ;
    printf(" ===>Affichage du systeme : \n\n\n");

    for(i = 0 ; i < A.size1() ; i++)
    {
        printf("  (");
        for(j = 0 ; j < A.size1() ; j++)
        {
            printf("  %.3f  ",A(i,j));
        }
        printf(" )    (X%d)   =",i+1);
        printf("\t%.3f",b[i]);
        printf("\n\n");
    }
}

/* Affichage de la solution du système */
void ConstrainGenetic::printSolution(std::vector<float> x)
{
    int i ;
    printf(" ===>Affichage de la solution : \n\n\n");

    for(i = 0 ; i < x.size() ; i++)
    {
        printf("(X%d)   =",i+1);
        printf("\t%.6f",x[i]);
        printf("\n\n");
    }
}

/* Méthode d'élimination de Gauss */
std::vector<float> ConstrainGenetic::gauss( boost::numeric::ublas::matrix<float> input, std::vector<float>& x, std::vector<float> b)/*(float **A, float *b, float *x, int n)*/
{
    int i, j, k ;
    int imin ;
    float p ;
    float sum, valmin, tump1, tump2 ;
    int n  = mListContrain->size();
    for(k = 0 ; k < n-1 ; k++)
    {
        /* Dans un premier temps, on cherche l'élément minimum (non */
        /* nul) en valeur absolue dans la colonne k et d'indice i   */
        /* supérieur ou égal à k.                                   */

        valmin = input(k,k) ; imin = k ;
        for(i = k+1 ; i < n ; i++)
        {
            if (valmin != 0)
            {
                if (abs(input(i,k)) < abs(valmin) && input(i,k) != 0)
                {
                    valmin = input(i,k) ;
                    imin = i ;
                }
            }
            else
            {
                valmin = input(i,k) ;
                imin = i ;
            }
        }

        /* Si l'élément minimum est nul, on peut en déduire */
        /* que la matrice est singulière. Le pogramme est   */
        /* alors interrompu.                                */

        if (valmin == 0.)
        {
            printf("\n\n\nAttention! Matrice singuliere!\n\n\n") ;
            exit( EXIT_FAILURE ) ;
        }

        /* Si la matrice n'est pas singulière, on inverse    */
        /* les éléments de la ligne imax avec les éléments   */
        /* de la ligne k. On fait de même avec le vecteur b. */

        for(j = 0 ; j < n ; j++)
        {
            tump1 = input(imin,j) ;
            input(imin,j) = input(k,j) ;
            input(k,j) = tump1 ;
        }

        tump2 = b[imin] ;
        b[imin] = b[k] ;
        b[k] = tump2 ;


        /* On procède à la réduction de la matrice par la */
        /* méthode d'élimination de Gauss. */

        for(i = k+1 ; i < n ; i++)
        {
            p = input(i,k)/input(k,k) ;

            for(j = 0 ; j < n ; j++)
            {
                input(i,j) = input(i,j) - p*input(k,j) ;
            }

            b[i] = b[i] - p*b[k] ;
        }
    }

    /* On vérifie que la matrice n'est toujours pas singulière. */
    /* Si c'est le cas, on interrompt le programme. */

    if (input(n-1,n-1) == 0)
    {
        printf("\n\n\nAttention! Matrice singuliere!\n\n\n") ;
        exit( EXIT_FAILURE ) ;
    }

    /* Une fois le système réduit, on obtient une matrice triangulaire */
    /* supérieure et la résolution du système se fait très simplement. */

    x[n-1] = b[n-1]/input(n-1,n-1) ;

    for(i = n-2 ; i > -1 ; i--){
        sum = 0 ;

        for(j = n-1 ; j > i ; j--){
            sum = sum + input(i,j)*x[j] ;
        }
        x[i] = (b[i] - sum)/input(i,i) ;
    }
    //printSolution(x);
    return x;
}

/*Constrain class*/


