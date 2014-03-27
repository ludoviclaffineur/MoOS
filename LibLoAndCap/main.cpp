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

Grid* TheGrid;
const char* filter ="";


int main(int argc, const char * argv[])
{
    using namespace std;
    pthread_setname_np("Main");
    TheGrid = new Grid();
    PcapHandler _pcap = PcapHandler(NULL, TheGrid);
    const char* osc1= "OSC1";
    TheGrid->addOutput(new OscHandler(osc1,"127.0.0.1","20000", "/osc", "f" ));
	_pcap.listAndChooseInterface();
    _pcap.loopThreading();
    // Control board

 /*   Genetic theGeneticAlgorithm = Genetic(TheGrid, false, 0.5, 0.2, 0.5,5);

    theGeneticAlgorithm.evalPop();
	cout << endl << endl << "Evolution de la population..." << endl;
	theGeneticAlgorithm.evolve();
	cout << "Population generation 2" << endl << endl << "Evaluation de la deuxieme generation";
    theGeneticAlgorithm.evalPop();
    float* best = theGeneticAlgorithm.getBest()->getCoeffs();

    for (int i = 0; i<TheGrid->getCells()->size();i++){
        cout<< "The best \t"<<best[i] << "\t" << flush;
    }*/

    std::cout<<"Lauching Web server http://127.0.0.1"<<std::endl;
    http::server::server s("0.0.0.0", "80", "./www", TheGrid);
    s.run();
    std::cout<<"Shuting down Web server..."<<std::endl;
    return 0;
}