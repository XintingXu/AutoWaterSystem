#include <uploadSensorInformation.h>
#include <QThread>
#include <QSemaphore>
#include <QString>
#include <QDrag>
#include <QtGui>
#include <QtWidgets>
#include <QNetworkReply>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <QString>

extern QSemaphore *PICaptureDone,*USBCaptureDone;
extern QSemaphore * QSemaphore_openPump1_done,* QSemaphore_openPump2_done, * QSemaphore_openPump3_done,*QSemaphore_openPump4_done;
extern bool RUNNING;
extern bool PUMP1_open,PUMP2_open,PUMP3_open,PUMP4_open,KEY1_press,KEY2_press,LQ1_high,LQ2_high;

ThreadUploadCapture1::ThreadUploadCapture1():QThread(){
    pro = new QProcess();
    cmdLocalHost = "/home/pi/uploadCapture1.sh";
    cmdYeelink = "/home/pi/capture1yeelink.sh";
}

ThreadUploadCapture1::~ThreadUploadCapture1(){
    delete(pro);
}

void ThreadUploadCapture1::run(){
    while(RUNNING){
        PICaptureDone->acquire(1);

        if(RUNNING){
            pro->execute(cmdLocalHost);
            pro->execute(cmdYeelink);

            emit threadLog("PI Capture is uploaded");
        }
    }
}

ThreadUploadCapture2::ThreadUploadCapture2():QThread(){
    pro = new QProcess();
    cmdLocalHost = "/home/pi/uploadCapture2.sh";
    cmdYeelink = "/home/pi/capture2yeelink.sh";
}

ThreadUploadCapture2::~ThreadUploadCapture2(){
    delete(pro);
}

void ThreadUploadCapture2::run(){
    while(RUNNING){
        USBCaptureDone->acquire(1);

        if(RUNNING){
            pro->execute(cmdLocalHost);
            pro->execute(cmdYeelink);

            emit threadLog("USB Capture is uploaded");
        }
    }
}

ThreadUploadPUMP1::ThreadUploadPUMP1():QThread(){
    pro = new QProcess();
}

ThreadUploadPUMP1::~ThreadUploadPUMP1(){
    delete(pro);
}

void ThreadUploadPUMP1::run(){
    while(RUNNING){
        QSemaphore_openPump1_done->acquire(1);

        if(!RUNNING){
            break;
        }
        if(PUMP1_open){
            //pro->execute("/home/pi/pumpUpload/pump1Upload_open.sh");
        }else{
            pro->execute("/home/pi/pumpUpload/pump1Upload_close.sh");
        }

        emit threadLog("Pump1 Updated");
    }
}


ThreadUploadPUMP2::ThreadUploadPUMP2():QThread(){
    pro = new QProcess();
}

ThreadUploadPUMP2::~ThreadUploadPUMP2(){
    delete(pro);
}

void ThreadUploadPUMP2::run(){
    while(RUNNING){
        QSemaphore_openPump2_done->acquire(1);

        if(!RUNNING){
            break;
        }

        if(PUMP2_open){
            //pro->execute("/home/pi/pumpUpload/pump2Upload_open.sh");
        }else{
            pro->execute("/home/pi/pumpUpload/pump2Upload_close.sh");
        }

        emit threadLog("Pump2 Updated");
    }
}


ThreadUploadPUMP3::ThreadUploadPUMP3():QThread(){
    pro = new QProcess();
}

ThreadUploadPUMP3::~ThreadUploadPUMP3(){
    delete(pro);
}

void ThreadUploadPUMP3::run(){
    while(RUNNING){
        QSemaphore_openPump3_done->acquire(1);

        if(!RUNNING){
            break;
        }

        if(PUMP3_open){
            //pro->execute("/home/pi/pumpUpload/pump3Upload_open.sh");
        }else{
            pro->execute("/home/pi/pumpUpload/pump3Upload_close.sh");
        }

        emit threadLog("Pump3 Updated");
    }
}


ThreadUploadPUMP4::ThreadUploadPUMP4():QThread(){
    pro = new QProcess();
}

ThreadUploadPUMP4::~ThreadUploadPUMP4(){
    delete(pro);
}

void ThreadUploadPUMP4::run(){
    while(RUNNING){
        QSemaphore_openPump4_done->acquire(1);

        if(!RUNNING){
            break;
        }

        if(PUMP4_open){
            //pro->execute("/home/pi/pumpUpload/pump4Upload_open.sh");
        }else{
            pro->execute("/home/pi/pumpUpload/pump4Upload_close.sh");
        }

        emit threadLog("Pump4 Updated");
    }
}
