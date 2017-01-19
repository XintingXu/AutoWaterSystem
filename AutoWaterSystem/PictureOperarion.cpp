#include "PictureOperation.h"

#include <QThread>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <QProcess>
#include <QString>
#include <QSemaphore>
#include <QTextBrowser>

extern QSemaphore * PICapture,*PICaptureDone;
extern QSemaphore *USBCapture,*USBCaptureDone;
extern cv::Mat capture1,capture2;
extern cv::Mat capture_USB;

extern bool RUNNING;

CapturePI::CapturePI():QThread(){
    //call the raspistill to capture picture through PI camera
    cmdLine = "raspistill -w 640 -h 480 -e jpg -ex auto -ifx denoise -o /home/pi/capture1.jpg -n -t 1000";
    poc = new QProcess;
}

CapturePI::~CapturePI(){
    delete(poc);
}

void CapturePI::run(){
    while(RUNNING){
        PICapture->acquire(1);

        if(!RUNNING){
            PICaptureDone->release(1);
            break;
        }

        poc->execute(cmdLine);
        capture1 = cv::imread("/home/pi/capture1.jpg");//load capture results
        cv::resize(capture1,capture1,cv::Size(128,96),0,0,cv::INTER_LINEAR);//resize the capture to be suitable for the UI
        PICaptureDone->release(1);
        emit threadLog(QString("PI capture ~/capture1.jpg"));
        emit showCapture();
    }
}

CaptureUSB::CaptureUSB():QThread(){//open usb camera and set capture info
    poc = new QProcess();
}

CaptureUSB::~CaptureUSB(){
    delete(poc);
}

void CaptureUSB::run(){
    while(RUNNING){
        USBCapture->acquire(1);

        if(!RUNNING){
            USBCaptureDone->release(1);
            break;
        }

        videoCap = cvCreateCameraCapture(1);
        cvSetCaptureProperty(videoCap,CV_CAP_PROP_FRAME_HEIGHT,480);
        cvSetCaptureProperty(videoCap,CV_CAP_PROP_FRAME_WIDTH,640);

        if(!videoCap){
            emit threadLog(QString("VideoCapture is not opened."));
        }else{
            frame = cvQueryFrame(videoCap);
            capture_USB = Mat(frame);
            cv::imwrite("/home/pi/capture2.jpg",capture_USB);//store the captured picture to the path
            cv::resize(capture_USB,capture2,cv::Size(128,96),0,0,cv::INTER_LINEAR);
            cv::cvtColor(capture2,capture2,CV_BGR2RGB);
            USBCaptureDone->release(1);
            emit threadLog(QString("USB Capture capture2.jpg"));
            emit showCapture();
        }
        cvReleaseCapture(&videoCap);
        cvReleaseImage(&frame);
    }
}
