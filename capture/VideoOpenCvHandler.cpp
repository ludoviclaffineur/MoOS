//
//  VideoOpenCvHandler.cpp
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 18/02/15.
//  Copyright (c) 2015 Ludovic Laffineur. All rights reserved.
//

#include "VideoOpenCvHandler.h"

using namespace cv;
using namespace std;

boost::mutex m_guard;
VideoOpenCvHandler::VideoOpenCvHandler(Grid* g){


}

VideoOpenCvHandler::~VideoOpenCvHandler(){
    cap->release();
    delete cap;
}

void VideoOpenCvHandler::init(){
std::cout<<"OK LANCE FRAME" <<std::endl;
    pthread_create(&capture_thread,NULL,VideoOpenCvHandler::videoHandler,this);
    //trackerThread = new boost::thread( boost::bind(videoHandler) );
    //capture_thread_boost = boost::thread(videoHandler);
    //trackerThread->join();

}

void* VideoOpenCvHandler::videoHandler(void* userdata){

    pthread_setname_np("VIDEO TRUC");

    
    VideoOpenCvHandler* VO = (VideoOpenCvHandler*) userdata;

    VO->cap = new VideoCapture(0);
    if (!VO->cap->isOpened())  // if not success, exit program
    {
        std::cout << "Cannot open the video cam" << endl;
    }

    double dWidth = VO->cap->get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
    double dHeight = VO->cap->get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

    std::cout << "Frame size : " << dWidth << " x " << dHeight << endl;
    namedWindow("MyVideo",CV_WINDOW_AUTOSIZE);
    Mat frame;  
    Mat frameNew;


    while (VO->cap->isOpened())
    {


        Mat frame;

        bool bSuccess = VO->cap->read(frame);
       // read a new frame from video
        std::cout<<frame.at<Vec3b>(0, 0)<<endl;

        //imshow("MyVideo", frame);
        //startWindowThread();
        //cv::updateWindow("MyVideo");
        /*if (!bSuccess) //if not success, break loop
        {
            std::cout << "Cannot read a frame from video stream" << endl;
            break;
        }else{
            cvtColor( frame, frame, CV_RGB2GRAY );
            threshold(frame, frame, 50, 255, THRESH_BINARY);
            imshow("MyVideo", frame); //show the frame in "MyVideo" window
        }*/


    }
    return NULL;
}