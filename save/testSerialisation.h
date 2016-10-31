//
//  testSerialisation.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 19/03/15.
//  Copyright (c) 2015 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__testSerialisation__
#define __LibLoAndCap__testSerialisation__

#include <stdio.h>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <vector>
#include <string>


class Test : public boost::archive::save_access{
public:
    Test(){}
    Test(int i, std::string c, float f1, float f2):  boost::archive::save_access (){
        a=i;
        s=c;
        v.push_back(f1);
        v.push_back(f2);

    }

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version){
        ar << a << s << v;
    }
    int a;
    std::string s;
    std::vector<float> v;
    
};



#endif /* defined(__LibLoAndCap__testSerialisation__) */
