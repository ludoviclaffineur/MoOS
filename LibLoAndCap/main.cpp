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


int main(int argc, const char * argv[])
{
    Grid* TheGrid;
    using namespace std;
    pthread_setname_np("Main");
    std::cout<<"\n------------------------------------------\n             Welcome in MoOS! \n------------------------------------------\nPlease choose your capture device in the list below:" <<std::endl;
    for(int  i =0 ;i<CaptureDeviceType::TOTAL; i++){
        std::cout<<i+1<<".\t"<< CaptureDeviceList[i]<<std::endl;
    }
    int choice;
    std::cout<<"Your choice:"<<std::flush;
    std::cin>>choice;
    choice--;


    TheGrid = new Grid();


    CaptureDevice* _captureDevice;
    switch (choice) {
        case CaptureDeviceType::PCAP_HANDLER:
            _captureDevice = new PcapHandler(NULL, TheGrid);
            break;
        case CaptureDeviceType::SERIAL_HANDLER:
            _captureDevice = new SerialHandler(TheGrid, "/dev/tty.usbmodem1411", 115200);
            break;
        default:
            _captureDevice = NULL;
            break;
    }
    const char* osc1= "OSC1";

    TheGrid->addOutput(new OscHandler(osc1,"127.0.0.1","20000", "/osc", "f" ));
	_captureDevice->init();
    // Control board

    Genetic* theGeneticAlgorithm = new Genetic(TheGrid, true, 0.5, 0.2, 0.5,5);
    theGeneticAlgorithm->evaluateAndEvolve(0.1);
    /*theGeneticAlgorithm.evalPop();
	cout << endl << endl << "Evolution de la population..." << endl;
	theGeneticAlgorithm.evolve();
	cout << "Population generation 2" << endl << endl << "Evaluation de la deuxieme generation";
    theGeneticAlgorithm.evalPop();
    float* best = theGeneticAlgorithm.getBest()->getCoeffs();

    for (int i = 0; i<TheGrid->getCells()->size();i++){
        cout<< "The best \t"<<best[i] << "\t" << flush;
    }*/

    std::cout<<"Lauching Web server http://127.0.0.1"<<std::endl;
    http::server::server s("0.0.0.0", "80", "./www", TheGrid, theGeneticAlgorithm);
    s.run();
    std::cout<<"\nShuting down Web server..."<<std::endl;
    delete _captureDevice;
    delete TheGrid;
    delete theGeneticAlgorithm;
    return 0;
}

