//
//  Parameter.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 6/02/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__Parameter__
#define __LibLoAndCap__Parameter__

#include <iostream>
#include <sstream>

class IParameter{

public:

    virtual const char* toString()=0;
    const char* getName(){
        return mName;
    }
    ~IParameter(){
        delete mName;
    }

protected:
    char* mName;

};


template<class T> class Parameter : public IParameter{

private:
    T* mData;

public:
    Parameter(const char* name, const T data){
        mName = new char [strlen(name) + 1];
        strcpy(mName, name);
        mData = new T [sizeof(&data)];
        std::memcpy(mData, &data, sizeof &data );
    }

    ~Parameter(){
        delete mData;
    }

    const char* toString() {
        std::stringstream stm;
        stm << **mData;
        //printf("Impression %s\n", stm.str().c_str());
        //s<<mGrid->getOutputs()->at(i)->getName();
        return stm.str().c_str();
    }
};

#endif /* defined(__LibLoAndCap__Parameter__) */
