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
#include <string.h>
#include <regex>
#include <sstream>

class PcapGrapAndStorePictures : public PcapProcessings {
public:
    PcapGrapAndStorePictures();
    void process (const u_char* data);
    void setActive (bool active);
private:
    void printPayload(const u_char *payload, int len);
    void printHexAsciiLine(const u_char *payload, int len, int offset);
    std::string convertPayloadToString(const u_char* payload, int size_payload);
};

#endif /* defined(__LibLoAndCap__PcapGrabAndStorePictures__) */
