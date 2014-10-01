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
    std::cout<<"\n------------------------------------------\n             Welcome in MoOS! \n------------------------------------------\n";
   /* for(int  i =0 ;i<CONSTANCES::CaptureDeviceType::TOTAL; i++){
        std::cout<<i+1<<".\t"<< CONSTANCES::CaptureDeviceList[i]<<std::endl;
    }
    int choice;
    std::cout<<"Your choice:"<<std::flush;
    std::cin>>choice;
    choice--;*/


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
/*    switch (choice) {
        case CONSTANCES::CaptureDeviceType::PCAP_HANDLER:
            _captureDevice = new PcapHandler("!udp port 8000", TheGrid);
            break;
        case CONSTANCES::CaptureDeviceType::SERIAL_HANDLER:
            _captureDevice = new SerialHandler(TheGrid, "/dev/tty.usbmodem1411", 115200);
            break;
        default:
            _captureDevice = NULL;
            break;
    }*/
    /*system("ls /dev/tty.usb*");
    string serialName;
    std::cin>>serialName;
    _captureDevice = new SerialHandler(TheGrid, serialName.c_str() , 115200);*/
    _captureDevice = new PcapHandler("!udp port 8000", TheGrid);

    //const char* osc1= "OSC1";
    _captureDevice->init();
   // TheGrid->addOutput(new OscHandler(osc1,"127.0.0.1","20000", "/osc", "f" ));
    //TheGrid->addOutput(new OscHandler("OSC2","127.0.0.1","20000", "/osc1", "f" ));
    //TheGrid->addOutput(new OscHandler("OSC3","127.0.0.1","20000", "/osc2", "f" ));
    //TheGrid->addOutput(new OscHandler("OSC4","127.0.0.1","20000", "/osc3", "f" ));

    // Control board

   Genetic* theGeneticAlgorithm = new Genetic(TheGrid, true, 0.5, 0.2, 0.5,5);
    //ConstrainGenetic* theConstrainAlgo = new ConstrainGenetic(TheGrid);
   /* int a;
    std::string KymaAddress;

    std::cout<<"Insert the IP address of your Pacarana device: "<<std::flush;
    std::cin>>KymaAddress;
    KymaHandler* k= new KymaHandler(KymaAddress.c_str(), "8000", TheGrid);
   // std::cout<< ""<<std::endl;
    std::cin>>a;*/

   /*theConstrainAlgo->setConstrain();
   while (a>0){ 
        std::cin>>a;
        theConstrainAlgo->setConstrain();

    }
    theConstrainAlgo->computeGrid();*/



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

    std::cout<<"Lauching Web server... you can access at http://127.0.0.1"<<std::endl;
    http::server::server s("0.0.0.0", "80", "/Users/ludoviclaffineur/Documents/LibLoAndCap/build/Release/www", TheGrid, theGeneticAlgorithm,theConstrainAlgo);
    s.run();
    std::cout<<"\nShuting down Web server..."<<std::endl;

    delete _captureDevice;
    delete TheGrid;
    delete theGeneticAlgorithm;
    return 0;
}

