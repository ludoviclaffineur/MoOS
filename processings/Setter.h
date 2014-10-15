//
//  Setter.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 14/10/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef LibLoAndCap_Setter_h
#define LibLoAndCap_Setter_h
template<class T> class Setter{
public:
    virtual void setValue(T t) = 0;
};

#endif
