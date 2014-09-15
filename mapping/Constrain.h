//
//  Constrain.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 8/09/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__Constrain__
#define __LibLoAndCap__Constrain__

#include <iostream>
#include <vector>


namespace IA {

class Constrain{
public:
    Constrain(std::vector<float>* inputsValues, std::vector<float>* outputsValues);
    std::vector<float>* mInputsValues;
    std::vector<float>* mOutputsValues;
private:

    //float mOutputsValue;
};


}
#endif /* defined(__LibLoAndCap__Constrain__) */
