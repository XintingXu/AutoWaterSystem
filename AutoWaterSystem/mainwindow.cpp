#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <QProcess>
#include <QSemaphore>
#include <PictureOperation.h>
#include <wiringPi.h>
#include <uploadSensorInformation.h>

bool RUNNING = true;//A very important value to judge whether the APP is running

QSemaphore *PICapture,*USBCapture,*Qsemphere_login;//Semaphore used to constrain CSI-Camera ,USB-Camera and log-Activity
QSemaphore *PICaptureDone,*USBCaptureDone;//Semaphore used to judge whether the capture process is done

QSemaphore * QSemaphore_openPump1,*QSemaphore_openPump2,*QSemaphore_openPump3,*QSemaphore_openPump4;
QSemaphore * QSemaphore_openPump1_done,* QSemaphore_openPump2_done, * QSemaphore_openPump3_done,*QSemaphore_openPump4_done;
QSemaphore * QSemaphore_pump1_changed,* QSemaphore_pump2_changed,* QSemaphore_pump3_changed,* QSemaphore_pump4_changed;

bool PUMP1_open,PUMP2_open,PUMP3_open,PUMP4_open,KEY1_press,KEY2_press,LQ1_high,LQ2_high;

using namespace cv;

cv::Mat capture1,capture2;//the shortcut of captured image
cv::Mat capture_USB;//the image captured bu the USB device

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //wiringPiSetup();
    InitPins();
    PUMP1_open = false;
    PUMP2_open = false;
    PUMP3_open = false;
    PUMP4_open = false;
    KEY1_press = false;
    KEY2_press = false;
    LQ1_high = true;
    LQ2_high = true;

    ui->setupUi(this);
    button_capture1 = ui->pushButton;
    button_capture2 = ui->pushButton_3;
    button_pump1 = ui->pushButton_4;
    button_pump2 = ui->pushButton_5;
    button_pump3 = ui->pushButton_6;
    button_pump4 = ui->pushButton_7;
    button_close = ui->pushButton_2;
    textBrowser = ui->textBrowser;
    label_capture1 = ui->label;
    label_capture2 = ui->label_2;
    textBrowser->document()->setMaximumBlockCount(50);

    button_pump1->setText("PUMP1 C");
    button_pump2->setText("PUMP2 C");
    button_pump3->setText("PUMP3 C");
    button_pump4->setText("PUMP4 C");

    connect(button_capture1,SIGNAL(released()),this,SLOT(capture1Button_clicked()));
    connect(button_capture2,SIGNAL(released()),this,SLOT(capture2Button_clicked()));
    connect(button_pump1,SIGNAL(released()),this,SLOT(pump1Button_clicked()));
    connect(button_pump2,SIGNAL(released()),this,SLOT(pump2Button_clicked()));
    connect(button_pump3,SIGNAL(released()),this,SLOT(pump3Button_clicked()));
    connect(button_pump4,SIGNAL(released()),this,SLOT(pump4Button_clicked()));
    connect(button_close,SIGNAL(pressed()),this,SLOT(exitButton_clicked()));
    connect(&capturePI,SIGNAL(threadLog(QString)),this,SLOT(Log(QString)),Qt::QueuedConnection);
    connect(&captureUSB,SIGNAL(threadLog(QString)),this,SLOT(Log(QString)),Qt::QueuedConnection);
    connect(&srunLog,SIGNAL(threadLog(QString)),this,SLOT(Log(QString)),Qt::QueuedConnection);
    connect(&threadControlPump1,SIGNAL(threadLog(QString)),this,SLOT(Log(QString)),Qt::QueuedConnection);
    connect(&threadControlPump2,SIGNAL(threadLog(QString)),this,SLOT(Log(QString)),Qt::QueuedConnection);
    connect(&threadControlPump3,SIGNAL(threadLog(QString)),this,SLOT(Log(QString)),Qt::QueuedConnection);
    connect(&threadControlPump4,SIGNAL(threadLog(QString)),this,SLOT(Log(QString)),Qt::QueuedConnection);
    connect(&threaduploadCapture1,SIGNAL(threadLog(QString)),this,SLOT(Log(QString)),Qt::QueuedConnection);
    connect(&threadUploadCapture2,SIGNAL(threadLog(QString)),this,SLOT(Log(QString)),Qt::QueuedConnection);
    connect(&threadUploadPUMP1,SIGNAL(threadLog(QString)),this,SLOT(Log(QString)),Qt::QueuedConnection);
    connect(&threadUploadPUMP2,SIGNAL(threadLog(QString)),this,SLOT(Log(QString)),Qt::QueuedConnection);
    connect(&threadUploadPUMP3,SIGNAL(threadLog(QString)),this,SLOT(Log(QString)),Qt::QueuedConnection);
    connect(&threadUploadPUMP4,SIGNAL(threadLog(QString)),this,SLOT(Log(QString)),Qt::QueuedConnection);
    connect(&capturePI,SIGNAL(showCapture()),this,SLOT(showCapture1()),Qt::QueuedConnection);
    connect(&captureUSB,SIGNAL(showCapture()),this,SLOT(showCapture2()),Qt::QueuedConnection);

    PICapture = new QSemaphore(0);
    USBCapture = new QSemaphore(0);
    Qsemphere_login = new QSemaphore(0);
    PICaptureDone = new QSemaphore(0);
    USBCaptureDone = new QSemaphore(0);
    QSemaphore_openPump1 = new QSemaphore(0);
    QSemaphore_openPump2 = new QSemaphore(0);
    QSemaphore_openPump3 = new QSemaphore(0);
    QSemaphore_openPump4 = new QSemaphore(0);
    QSemaphore_openPump1_done = new QSemaphore(0);
    QSemaphore_openPump2_done = new QSemaphore(0);
    QSemaphore_openPump3_done = new QSemaphore(0);
    QSemaphore_openPump4_done = new QSemaphore(0);
    QSemaphore_pump1_changed = new QSemaphore(0);
    QSemaphore_pump2_changed = new QSemaphore(0);
    QSemaphore_pump3_changed = new QSemaphore(0);
    QSemaphore_pump4_changed = new QSemaphore(0);

    capturePI.start();
    captureUSB.start();
    srunLog.start();
    threadControlPump1.start();
    threadControlPump2.start();
    threadControlPump3.start();
    threadControlPump4.start();
    threaduploadCapture1.start();
    threadUploadCapture2.start();
    threadUploadPUMP1.start();
    threadUploadPUMP2.start();
    threadUploadPUMP3.start();
    threadUploadPUMP4.start();
    getpump1fromlocal.start();
    getpump1fromyeelink.start();
    getpump2fromlocal.start();
    getpump2fromyeelink.start();
    getpump3fromlocal.start();
    getpump3fromyeelink.start();
    getpump4fromlocal.start();
    getpump4fromyeelink.start();
    getcapture1fromlocal.start();
    getcapture2fromlocal.start();;
    getcapture1fromyeelink.start();
    getcapture2fromyeelink.start();
}

void MainWindow::InitPins(){
    pinMode(PIN_CONTROL1,OUTPUT);
    pinMode(PIN_CONTROL2,OUTPUT);
    pinMode(PIN_CONTROL3,OUTPUT);
    pinMode(PIN_CONTROL4,OUTPUT);

    pinMode(PIN_TRAN1,OUTPUT);
    pinMode(PIN_TRAN2,OUTPUT);
    pinMode(PIN_TRAN3,OUTPUT);

    pinMode(PIN_LQ1,INPUT);
    pinMode(PIN_LQ2,INPUT);

    pinMode(PIN_KEY1,INPUT);
    pinMode(PIN_KEY2,INPUT);

    digitalWrite(PIN_CONTROL1,HIGH);
    digitalWrite(PIN_CONTROL2,HIGH);
    digitalWrite(PIN_CONTROL3,HIGH);
    digitalWrite(PIN_CONTROL4,HIGH);

    digitalWrite(PIN_TRAN1,HIGH);
    digitalWrite(PIN_TRAN2,HIGH);
    digitalWrite(PIN_TRAN3,HIGH);

    digitalWrite(PIN_LQ1,HIGH);
    digitalWrite(PIN_LQ2,HIGH);

    digitalWrite(PIN_KEY1,HIGH);
    digitalWrite(PIN_KEY2,HIGH);
}

MainWindow::~MainWindow(){
    delete(PICapture);
    delete(USBCapture);
    delete(Qsemphere_login);
    delete(PICaptureDone);
    delete(USBCaptureDone);
    delete(QSemaphore_openPump1);
    delete(QSemaphore_openPump2);
    delete(QSemaphore_openPump3);
    delete(QSemaphore_openPump4);
    delete(QSemaphore_openPump1_done);
    delete(QSemaphore_openPump2_done);
    delete(QSemaphore_openPump3_done);
    delete(QSemaphore_openPump4_done);
    delete ui;
}

void MainWindow::capture1Button_clicked(){
    PICapture->release(1);
}

void MainWindow::capture2Button_clicked(){
    USBCapture->release(1);
}

void MainWindow::pump1Button_clicked(){
    if(PUMP1_open){
        PUMP1_open = !PUMP1_open;
        button_pump1->setText("PUMP1 C");
        QSemaphore_openPump1->release(1);
    }else{
        PUMP1_open = !PUMP1_open;
        button_pump1->setText("PUMP1 O");
        QSemaphore_openPump1->release(1);
    }
}

void MainWindow::pump2Button_clicked(){
    if(PUMP2_open){
        PUMP2_open = !PUMP2_open;
        button_pump2->setText("PUMP2 C");
        QSemaphore_openPump2->release(1);
    }else{
        PUMP2_open = !PUMP2_open;
        button_pump2->setText("PUMP2 O");
        QSemaphore_openPump2->release(1);
    }
}

void MainWindow::pump3Button_clicked(){
    if(PUMP3_open){
        PUMP3_open = !PUMP3_open;
        button_pump3->setText("PUMP3 C");
        QSemaphore_openPump3->release(1);
    }else{
        PUMP3_open = !PUMP3_open;
        button_pump3->setText("PUMP3 O");
        QSemaphore_openPump3->release(1);
    }
}

void MainWindow::pump4Button_clicked(){
    if(PUMP4_open){
        PUMP4_open = !PUMP4_open;
        button_pump4->setText("PUMP4 C");
        QSemaphore_openPump4->release(1);
    }else{
        PUMP4_open = !PUMP4_open;
        button_pump4->setText("PUMP4 O");
        QSemaphore_openPump4->release(1);
    }
}

void MainWindow::exitButton_clicked(){
    RUNNING = false;

    PICapture->release(1);
    USBCapture->release(1);
    Qsemphere_login->release(1);
    QSemaphore_openPump1->release(1);
    QSemaphore_openPump2->release(1);
    QSemaphore_openPump3->release(1);
    QSemaphore_openPump4->release(1);
    QSemaphore_openPump1_done->release(1);
    QSemaphore_openPump2_done->release(1);
    QSemaphore_openPump3_done->release(1);
    QSemaphore_openPump4_done->release(1);

    capturePI.wait();
    captureUSB.wait();
    srunLog.wait();
    threadControlPump1.wait();
    threadControlPump2.wait();
    threadControlPump3.wait();
    threadControlPump4.wait();
    threaduploadCapture1.wait();
    threadUploadCapture2.wait();
    threadUploadPUMP1.wait();
    threadUploadPUMP2.wait();
    threadUploadPUMP3.wait();
    threadUploadPUMP4.wait();
    getpump1fromlocal.wait();
    getpump1fromyeelink.wait();
    getpump2fromlocal.wait();
    getpump2fromyeelink.wait();
    getpump3fromlocal.wait();
    getpump3fromyeelink.wait();
    getpump4fromlocal.wait();
    getpump4fromyeelink.wait();
    getcapture1fromlocal.wait();
    getcapture2fromlocal.wait();
    getcapture1fromyeelink.wait();
    getcapture2fromyeelink.wait();

    close();
}

void MainWindow::on_textBrowser_textChanged(){
    ui->textBrowser->moveCursor(QTextCursor::End);
}

void MainWindow::Log(QString textMessage){
    textBrowser->append(textMessage);
}

void MainWindow::showCapture1(){
    label_capture1->setPixmap(QPixmap::fromImage(QImage(capture1.data,capture1.cols,capture2.rows,QImage::Format_RGB888)));
}

void MainWindow::showCapture2(){
    label_capture2->setPixmap(QPixmap::fromImage(QImage(capture2.data,capture2.cols,capture2.rows,QImage::Format_RGB888)));
}
