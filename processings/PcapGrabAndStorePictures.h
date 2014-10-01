//
//  PcapGrabAndStorePictures.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 1/10/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__PcapGrabAndStorePictures__
#define __LibLoAndCap__PcapGrabAndStorePictures__

#include <iostream>
#include "PcapProcessings.h"

class PcapGrapAndStorePictures : public PcapProcessings {
    PcapGrapAndStorePictures();
    void process (const u_char* data);
    void setActive (bool active);
};

#endif /* defined(__LibLoAndCap__PcapGrabAndStorePictures__) */
