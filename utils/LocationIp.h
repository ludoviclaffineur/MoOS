//
//  CsvRow.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 3/03/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__CsvRow__
#define __LibLoAndCap__CsvRow__

#include <iostream>
class LocationIp{
public:
    LocationIp(unsigned long int ipbegin, short int latitude, short int longitude);
    unsigned long int getIpBegin();
    short int getLongitude();
    short int getLatitude();
private:
    unsigned long int mIpBegin;  //need 4 bytes for IP address
    short int mLatitude;
    short int mLongitude;

};

#endif /* defined(__LibLoAndCap__CsvRow__) */
