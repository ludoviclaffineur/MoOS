//
//  PcapPasswordsProcessing.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 8/04/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__PcapPasswordsProcessing__
#define __LibLoAndCap__PcapPasswordsProcessing__

#include <iostream>
#include "PcapProcessings.h"



class PcapPasswordsProcessing : public PcapProcessings {
public:
    PcapPasswordsProcessing();
    void setActive(bool active);
    //void process(const u_char* datas);
    void process(const u_char* data);
    void setLength(int length);

private:
    int mLength;
};
#endif /* defined(__LibLoAndCap__PcapPasswordsProcessing__) */
