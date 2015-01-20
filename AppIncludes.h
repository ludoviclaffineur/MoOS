//
//  AppIncludes.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 30/10/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#ifndef LibLoAndCap_AppIncludes_h
#define LibLoAndCap_AppIncludes_h

#include <iostream>
#include "OscHandler.h"
#include "PcapHandler.h"
#include "CaptureDevice.h"
#include "Converter.h"
#include "IpHeaderDefinitions.h"
#include "Grid.h"


namespace CONSTANCES {
    enum CaptureDeviceType{
        PCAP_HANDLER ,
        SERIAL_HANDLER,
        LEAPMOTION_HANDLER,
        READWAV_HANDLER,
        ODBC_HANDLER,
        TOTAL,
    };
    const std::string CaptureDeviceList [CaptureDeviceType::TOTAL] = {"Pcap Handler", "Serial Handler", "LeapMotion Handler", "ReadWave Handler", "ODBC Handler"};

}


#endif