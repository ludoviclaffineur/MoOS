//
//  VideoOpenCvHandler.h
//  LibLoAndCap
//
//  Created by Ludovic Laffineur on 18/02/15.
//  Copyright (c) 2015 Ludovic Laffineur. All rights reserved.
//

#ifndef __LibLoAndCap__VideoOpenCvHandler__
#define __LibLoAndCap__VideoOpenCvHandler__

#include <stdio.h>
#include "Grid.h"
#include "CaptureDevice.h"
#include <opencv2/opencv.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/lock_guard.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/recursive_mutex.hpp>


class VideoOpenCvHandler : public CaptureDevice{
public:
    void init();
    VideoOpenCvHandler(Grid* g);
    ~VideoOpenCvHandler();
    static void* videoHandler(void*);
    std::mutex imageLock;
    //void read_some();
    cv::VideoCapture* cap;
    pthread_mutex_t mutex_init=PTHREAD_MUTEX_INITIALIZER;

private:

    pthread_t capture_thread;
    boost::thread capture_thread_boost;
    boost::thread *trackerThread;
};

#endif /* defined(__LibLoAndCap__VideoOpenCvHandler__) */
