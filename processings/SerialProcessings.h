//
//  SerialProcessings.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 2/04/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef LibLoAndCap_SerialProcessings_h
#define LibLoAndCap_SerialProcessings_h
#include "Processings.h"

struct size_char_tab{
    int size;
    char* tab;
};

class SerialProcessings : public Processings {
    
public:

    
    SerialProcessings(){};
    virtual void setActive(bool active) = 0;
    //virtual void process(const u_char* datas) = 0;
    virtual void process (size_char_tab data) =0;
    void process(void* vdata){
        process ((*(size_char_tab*) vdata));
    };
    virtual void setSetter(int nbrSetter,...)=0;
    //virtual void process();
};

#endif
