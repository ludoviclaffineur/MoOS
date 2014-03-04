//
//  CsvImporter.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 3/03/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "CsvImporter.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>


void/*CsvRow**/ CsvImporter::importCsv(std::string &file){
    //std::fstream filestream (file);

    LocationIp** importedData = new LocationIp*[1893989];

    std::ifstream filestream (file, std::ifstream::in);
    if (filestream) {
        std::string line;
        std::smatch m_output;

        std::regex e_output ("([^\"]+),([^\"]+),([^\"^\\s]+)");
        unsigned long int IpBegin;  //need 4 bytes for IP address
        short int iLatitude;
        short int iLongitude;
        int i = 0;
        auto begin = std::chrono::high_resolution_clock::now() ;
        std::cout<< "Loading...";
        while (filestream.good()) {
            getline(filestream, line, ',');
            IpBegin = strtol(m_output[1].str().c_str(),NULL, 10);
            //std::cout<< line <<std::endl;
            getline(filestream, line, ',');
            iLatitude = atoi(m_output[2].str().c_str());
            //std::cout<< line <<std::endl;
            getline(filestream, line, '\n');
            iLongitude = atoi(m_output[3].str().c_str());
            //std::cout<< line <<std::endl;
            importedData[i++] = new LocationIp(IpBegin, iLatitude, iLongitude);
            if (i % (189398) ==0){
                std::cout<< i /18939 <<"% == " <<std::flush;
            }
        }
        std::cout<<"...  done"<<std::endl;
    }
}