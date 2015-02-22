//
//  main.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 30/10/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#include "AppIncludes.h"
#include "CaptureDevice.h"
#include "server.hpp"
#include <pthread.h>
#include "CsvImporter.h"
#include "Genetic.h"
#include "SerialHandler.h"
#include "PcapHandler.h"
#include "KymaHandler.h"
#include "ConstrainGenetic.h"
#include "LeapMotionHandler.h"
#include "ReadWavFileHandler.h"
#include "OdbcHandler.h"

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>

#include "GranularSyntheziser.h"
#include "GSDurationHandler.h"
#include "GSOverlapHandler.h"
#include "GSBlankHandler.h"
#include "GSReverbDecayHandler.h"
#include "GSReverbDelayHandler.h"
#include "GSLowPassCutoffHandler.h"
#include "GSInitPositionHandler.h"

#include "MidiHandler.h"

#include "MidiNoteHandler.h"
#include "MidiNoteDurationHandler.h"
#include "MidiNoteVelocityHandler.h"
#include "MidiNoteKeyHandler.h"
#include "MidiControlChange.h"

#include "WebSocketServer.h"

#include <opencv2/opencv.hpp>
//#include "storage_adaptors.hpp"


int main(int argc, const char * argv[])
{
    Grid* theGrid;
    using namespace boost::numeric::ublas;
    using namespace std;
//    pthread_setname_np("Main");
    std::cout<<"\n------------------------------------------\n             Welcome in MoOS! \n------------------------------------------\n";
  /*  for(int  i =0 ;i<CONSTANCES::CaptureDeviceType::TOTAL; i++){
        std::cout<<i+1<<".\t"<< CONSTANCES::CaptureDeviceList[i]<<std::endl;
    }
    int choice;
    std::cout<<"Your choice:"<<std::flush;
    std::cin>>choice;
    choice--;*/
    WebSocketServer* theWebSocketServer = new WebSocketServer(9002);
    theWebSocketServer->start();

    theGrid = new Grid();

    ConstrainGenetic* theConstrainAlgo = new ConstrainGenetic(theGrid);


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
    OdbcHandler* p = NULL;
   /* CaptureDevice* theCaptureDevice;
    switch (choice) {
        case CONSTANCES::CaptureDeviceType::PCAP_HANDLER:
            theCaptureDevice = new PcapHandler("!udp port 8000", theGrid);
            break;
        case CONSTANCES::CaptureDeviceType::SERIAL_HANDLER:
            theCaptureDevice = new SerialHandler(theGrid, "/dev/tty.usbmodem1411", 115200);
            break;
        case CONSTANCES::CaptureDeviceType::LEAPMOTION_HANDLER:
            theCaptureDevice = new LeapMotionHandler(theGrid);
            break;
        case CONSTANCES::CaptureDeviceType::READWAV_HANDLER:
            theCaptureDevice = new ReadWavFileHandler(theGrid,"/Users/ludoviclaffineur/Documents/LibLoAndCap/data/sinus440_1000.wav");
            break;
        case CONSTANCES::CaptureDeviceType::ODBC_HANDLER:
            theCaptureDevice = new OdbcHandler(theGrid,"filedsn=/Users/ludoviclaffineur/Documents/LibLoAndCap/build/Release/psql.dsn");
            p = (OdbcHandler*) theCaptureDevice;
            break;
        default:
            theCaptureDevice = NULL;
            break;
    }
*/

  //  theCaptureDevice->init();
    /*system("ls /dev/tty.usb*");
    string serialName;
    std::cin>>serialName;
    _captureDevice = new SerialHandler(TheGrid, serialName.c_str() , 115200);*/

    //_captureDevice =

    //const char* osc1= "OSC1";

   // TheGrid->addOutput(new OscHandler(osc1,"127.0.0.1","20000", "/osc", "f" ));
    //TheGrid->addOutput(new OscHandler("OSC2","127.0.0.1","20000", "/osc1", "f" ));
    //TheGrid->addOutput(new OscHandler("OSC3","127.0.0.1","20000", "/osc2", "f" ));
    //TheGrid->addOutput(new OscHandler("OSC4","127.0.0.1","20000", "/osc3", "f" ));



/*     MidiHandler* mh = new MidiHandler();
    MidiNoteHandler* MNH = new MidiNoteHandler(mh);
    theGrid->addOutput(new MidiControlChange(mh));
    theGrid->addOutput(new MidiNoteVelocityHandler(MNH));
    theGrid->addOutput(new MidiNoteKeyHandler(MNH));
    theGrid->addOutput(new MidiNoteDurationHandler(MNH));
*/





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


    //GRANULAR SYNTH
    /*
    GranularSyntheziser *gs = new GranularSyntheziser();
    theGrid->addOutput(new GSDurationHandler(gs));
    theGrid->addOutput(new GSOverlapHandler(gs));
    theGrid->addOutput(new GSBlankHandler(gs));
    theGrid->addOutput(new GSReverbDecayHandler(gs));
    theGrid->addOutput(new GSReverbDelayHandler(gs));
    theGrid->addOutput(new GSLowPassCutoffHandler(gs));
    theGrid->addOutput(new GSInitPositionHandler(gs));*/





    Genetic* theGeneticAlgorithm = new Genetic(theGrid, true, 0.5, 0.2, 0.5,5);
     //theGeneticAlgorithm->reinit();
    //theGeneticAlgorithm->evaluateAndEvolve(0.1);
//    theGeneticAlgorithm->evalPop();
//	cout << endl << endl << "Evolution de la population..." << endl;
//	theGeneticAlgorithm->evolve();
//	cout << "Population generation 2" << endl << endl << "Evaluation de la deuxieme generation";
//    theGeneticAlgorithm->evalPop();
//    float* best = theGeneticAlgorithm->getBest()->getCoeffs();
//
//    for (int i = 0; i<theGrid->getCells()->size();i++){
//        cout<< "The best \t"<<best[i] << "\t" << flush;
//    }
    //delete k;
 /*   using namespace cv;
    using namespace std;
    
   // WebSocketServer serverSoc(9002);
    std::cout<< "INIIIIIT WEBCAM" <<std::endl;
    // open the video camera no. 0
    cv::VideoCapture* cap;
    cap = new VideoCapture(0);
    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    if (!cap->isOpened())  // if not success, exit program
    {
        std::cout << "Cannot open the video cam" << endl;
    }

    double dWidth = cap->get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
    double dHeight = cap->get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

    std::cout << "Frame size : " << dWidth << " x " << dHeight << endl;

    namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

    //createTrackbar( TrackbarName, "Linear Blend", &tresh, 255.0, on_trackbar );
    // createTrackbar(TrackbarName, "Linear Blend", int *value, int count)
    while (1)
    {
        Mat frame;

        bool bSuccess = cap->read(frame); // read a new frame from video

        if (!bSuccess) //if not success, break loop
        {
            std::cout << "Cannot read a frame from video stream" << endl;
            break;
        }else{
            cvtColor( frame, frame, CV_RGB2GRAY );
            threshold(frame, frame, 0, 255, THRESH_OTSU);
            imshow("MyVideo", frame); //show the frame in "MyVideo" window
        }


        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            cout << "esc key is pressed by user" << endl;
            break; 
        }
    }*/


    std::cout<<"Lauching Web server... you can access at http://127.0.0.1"<<std::endl;
    http::server::server s("0.0.0.0", "80", "/Users/ludoviclaffineur/Documents/LibLoAndCap/build/Release/www", theGrid, theGeneticAlgorithm,theConstrainAlgo, p);
    s.run();
    std::cout<<"\nShuting down Web server..."<<std::endl;
    //delete theCaptureDevice;
    delete theGrid;
    delete theGeneticAlgorithm;
    theWebSocketServer->sendStopMessage();
    delete theWebSocketServer;
   // delete gs;
    return 0;
}

