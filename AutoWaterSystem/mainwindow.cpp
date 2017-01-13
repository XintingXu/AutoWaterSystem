#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    button = ui->pushButton;
    button_close = ui->pushButton_2;

    connect(button,SIGNAL(released()),this,SLOT(on_openButton_clicked()));
    connect(button_close,SIGNAL(pressed()),this,SLOT(on_closeButton_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openButton_clicked()
{
    VideoCapture videoCap;
    videoCap.open(0);
    if(!videoCap.isOpened()){
        cout << "Cannot open camera" << endl;
    }else{
        videoCap.set(CV_CAP_PROP_FRAME_HEIGHT,360);
        videoCap.set(CV_CAP_PROP_FRAME_WIDTH,640);
        videoCap.set(CV_CAP_PROP_FPS,30);
        Mat frame;
        videoCap.read(frame);
        cvtColor(frame,frame,CV_BGR2RGB);
        ui->label->setPixmap(QPixmap::fromImage(QImage(frame.data,frame.cols,frame.rows,QImage::Format_RGB888)));
        videoCap.release();
    }
}

void MainWindow::on_closeButton_clicked()
{
    close();
}
