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

bool RUNNING = true;//A very important value to judge whether the APP is running

QSemaphore *PICapture,*USBCapture,*Qsemphere_login;//Semaphore used to constrain CSI-Camera ,USB-Camera and log-Activity
QSemaphore *PICaptureDone,*USBCaptureDone;//Semaphore used to judge whether the capture process is done

using namespace cv;

cv::Mat capture1,capture2;//the shortcut of captured image
cv::Mat capture_USB;//the image captured bu the USB device

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    button = ui->pushButton;
    button_close = ui->pushButton_2;
    textBrowser = ui->textBrowser;
    label_capture1 = ui->label;
    label_capture2 = ui->label_2;
    textBrowser->document()->setMaximumBlockCount(50);

    connect(button,SIGNAL(released()),this,SLOT(openButton_clicked()));
    connect(button_close,SIGNAL(pressed()),this,SLOT(closeButton_clicked()));
    connect(&capturePI,SIGNAL(threadLog(QString)),this,SLOT(Log(QString)),Qt::QueuedConnection);
    connect(&captureUSB,SIGNAL(threadLog(QString)),this,SLOT(Log(QString)),Qt::QueuedConnection);
    connect(&srunLog,SIGNAL(threadLog(QString)),this,SLOT(Log(QString)),Qt::QueuedConnection);
    connect(&capturePI,SIGNAL(showCapture()),this,SLOT(showCapture1()),Qt::QueuedConnection);
    connect(&captureUSB,SIGNAL(showCapture()),this,SLOT(showCapture2()),Qt::QueuedConnection);

    PICapture = new QSemaphore(0);
    USBCapture = new QSemaphore(0);
    Qsemphere_login = new QSemaphore(0);
    PICaptureDone = new QSemaphore(0);
    USBCaptureDone = new QSemaphore(0);

    capturePI.start();
    captureUSB.start();
    srunLog.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openButton_clicked()
{
    USBCapture->release(1);

    PICapture->release(1);
}

void MainWindow::closeButton_clicked()
{
    RUNNING = false;

    PICapture->release(1);
    USBCapture->release(1);
    Qsemphere_login->release(1);

    capturePI.wait();
    captureUSB.wait();
    srunLog.wait();

    close();
}

void MainWindow::on_textBrowser_textChanged()
{
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
