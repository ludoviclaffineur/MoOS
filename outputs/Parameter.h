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

class IParameter{

public:
    void* getValue();
    const char* getName(){
        return mName;
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
        delete mName;
        delete mData;
    }
    
    T getValue(){
        return *mData;
    }
};

#endif /* defined(__LibLoAndCap__Parameter__) */
