//
//  Processings.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 13/03/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__Processings__
#define __LibLoAndCap__Processings__

//! Mother Class of all the processings
class Processings{

public:
    //! activate the processing or not
    virtual void setActive(bool active) = 0;
    //! return if the processing is active
    bool isActive(){return mActive;}
    //! where the process will take part
    virtual void process (void* vdata) = 0;

protected:
    //! processing active
    bool mActive;
    //! permit user to give setter for computed values of the processing
    //! @param nbrSetter amount of setters,
    //! @param ... setters
    virtual void setSetter(int nbrSetter,...) = 0;
};




#endif /* defined(__LibLoAndCap__Processings__) */
