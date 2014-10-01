//
//  PcapGrabAndStorePictures.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 1/10/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "PcapGrabAndStorePictures.h"


PcapGrapAndStorePictures::PcapGrapAndStorePictures(){

}


void PcapGrapAndStorePictures::process (const u_char* data){
    if (mActive) {
        
    }
}

void PcapGrapAndStorePictures::setActive (bool active){
    mActive = active;
}
