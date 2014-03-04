//
//  CsvRow.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 3/03/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "CsvRow.h"

CsvRow::CsvRow(unsigned long int ipbegin, short int latitude, short int longitude){
    mIpBegin = ipbegin;
    mLatitude = latitude;
    mLongitude = longitude;
}

unsigned long int CsvRow::getIpBegin(){
    return mIpBegin;
}
