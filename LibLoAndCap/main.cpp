//
//  main.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 30/10/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#include "AppIncludes.h"
#include "server.hpp"
#include <pthread.h>
#include "CsvImporter.h"
#include "Genetic.h"
#include "SerialHandler.h"
#include "KymaHandler.h"
#include "ConstrainGenetic.h"

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>
//#include "storage_adaptors.hpp"

int main(int argc, const char * argv[])
{
    Grid* TheGrid;
    using namespace boost::numeric::ublas;
    using namespace std;
//    pthread_setname_np("Main");
    std::cout<<"\n------------------------------------------\n             Welcome in MoOS! \n------------------------------------------\nPlease choose your capture device in the list below:" <<std::endl;
    for(int  i =0 ;i<CONSTANCES::CaptureDeviceType::TOTAL; i++){
        std::cout<<i+1<<".\t"<< CONSTANCES::CaptureDeviceList[i]<<std::endl;
    }
    int choice;
    std::cout<<"Your choice:"<<std::flush;
    std::cin>>choice;
    choice--;


    TheGrid = new Grid();

    ConstrainGenetic* theConstrainAlgo = new ConstrainGenetic(TheGrid);


//	matrix<float> A(3, 3), Z(3, 3);
//    A(0, 0) = 1;
//    A(0,1) = 2;
//    A(0,2) = 3;
//
//    A(1,0) = 5;
//    A(1,1) = 1;
//    A(1,2) = 4;
//
//    A(2,0) = 6;
//    A(2,1) = 7;
//    A(2,2) = 1;
//
//	theConstrainAlgo->invertMatrix(A, Z);
//
//	cout << "A=" << A << endl << "Z=" << Z <<"IDENTITY" << prod(A, Z)<< endl;

    CaptureDevice* _captureDevice;
    switch (choice) {
        case CONSTANCES::CaptureDeviceType::PCAP_HANDLER:
            _captureDevice = new PcapHandler("TCP and UDP and ICMP and !udp port 8000", TheGrid);
            break;
        case CONSTANCES::CaptureDeviceType::SERIAL_HANDLER:
            _captureDevice = new SerialHandler(TheGrid, "/dev/tty.usbmodem1411", 115200);
            break;
        default:
            _captureDevice = NULL;
            break;
    }
    const char* osc1= "OSC1";

    TheGrid->addOutput(new OscHandler("sposx","127.0.0.1","12000", "/sposx", "f" ));
    TheGrid->addOutput(new OscHandler("sposy","127.0.0.1","12000", "/sposy", "f" ));
    TheGrid->addOutput(new OscHandler("dposx","127.0.0.1","12000", "/dposx", "f" ));
    TheGrid->addOutput(new OscHandler("dposy","127.0.0.1","12000", "/dposy", "f" ));
    TheGrid->addOutput(new OscHandler("density","127.0.0.1","12000", "/density", "f" ));
    TheGrid->addOutput(new OscHandler("DHCP","127.0.0.1","12000", "/dhcp", "f" ));
	_captureDevice->init();
    // Control board //

    //192.168.240.89

    Genetic* theGeneticAlgorithm = new Genetic(TheGrid, true, 0.5, 0.2, 0.5,5);
    //ConstrainGenetic* theConstrainAlgo = new ConstrainGenetic(TheGrid);
    int a;
    //KymaHandler* k= new KymaHandler("192.168.240.53", "8000", TheGrid);
    std::cin>>a;
/*
   theConstrainAlgo->setConstrain();
   while (a>0){ 
        std::cin>>a;
        theConstrainAlgo->setConstrain();

    }
    theConstrainAlgo->computeGrid();
*/


    //theGeneticAlgorithm->evaluateAndEvolve(0.1);
    /*theGeneticAlgorithm.evalPop();
	cout << endl << endl << "Evolution de la population..." << endl;
	theGeneticAlgorithm.evolve();
	cout << "Population generation 2" << endl << endl << "Evaluation de la deuxieme generation";
    theGeneticAlgorithm.evalPop();
    float* best = theGeneticAlgorithm.getBest()->getCoeffs();

    for (int i = 0; i<TheGrid->getCells()->size();i++){
        cout<< "The best \t"<<best[i] << "\t" << flush;
    }*/

    //delete k;

    std::cout<<"Lauching Web server..."<<std::endl;
    http::server::server s("0.0.0.0", "80", "/Users/ludoviclaffineur/Documents/LibLoAndCap/build/Release/www", TheGrid, theGeneticAlgorithm);
    s.run();
    std::cout<<"\nShuting down Web server..."<<std::endl;

    delete _captureDevice;
    delete TheGrid;
    delete theGeneticAlgorithm;
    return 0;
}

