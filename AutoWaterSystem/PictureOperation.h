#ifndef PICTUREOPERATION_H
#define PICTUREOPERATION_H

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

extern bool RUNNING;

class CapturePI:public QThread{//capture a picture through PI camera
    Q_OBJECT
private:
    QString cmdLine;//used to run the .sh file to complish the capture procedure
    QProcess *poc;

signals:
    void threadLog(QString textMessage);
    void showCapture();

public:
    CapturePI();
    void run();
    ~CapturePI();
};

class CaptureUSB : public QThread{
    Q_OBJECT
private:
    cv::VideoCapture videoCap;

signals:
    void threadLog(QString textMessage);
    void showCapture();

public:
    CaptureUSB();
    ~CaptureUSB();
    void run();
};


#endif // PICTUREOPERATION_H
