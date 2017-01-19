#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QImage>
#include <QWidget>
#include <QTimer>
#include <QTextBrowser>
#include <QLabel>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <NetworkOperation.h>
#include <PictureOperation.h>
#include <DeviceControl.h>
#include <uploadSensorInformation.h>
#include <getSensorInformation.h>

#define PIN_CONTROL1 26
#define PIN_CONTROL2 27
#define PIN_CONTROL3 28
#define PIN_CONTROL4 29

#define PIN_TRAN1 23
#define PIN_TRAN2 24
#define PIN_TRAN3 25

#define PIN_LQ1 21
#define PIN_LQ2 22

#define PIN_KEY1 1
#define PIN_KEY2 4

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void Log(QString textMessage);//show texts in the textBrowser
    void showCapture1();//show shortcut of picture captured by PI camera
    void showCapture2();//show shortcut of picture captured by USB camera

private slots:
    void capture1Button_clicked();
    void capture2Button_clicked();
    void pump1Button_clicked();
    void pump2Button_clicked();
    void pump3Button_clicked();
    void pump4Button_clicked();
    void exitButton_clicked();
    void on_textBrowser_textChanged();

private:
    void InitPins();
    Ui::MainWindow *ui;
    QPushButton *button_capture1;
    QPushButton *button_capture2;
    QPushButton *button_pump1;
    QPushButton *button_pump2;
    QPushButton *button_pump3;
    QPushButton *button_pump4;
    QPushButton *button_close;

    QTextBrowser *textBrowser;
    QLabel *label_capture1;
    QLabel *label_capture2;

    CapturePI capturePI;
    CaptureUSB captureUSB;
    SrunLogIn srunLog;
    ThreadControlPump1 threadControlPump1;
    ThreadControlPump2 threadControlPump2;
    ThreadControlPump3 threadControlPump3;
    ThreadControlPump4 threadControlPump4;
    ThreadUploadCapture1 threaduploadCapture1;
    ThreadUploadCapture2 threadUploadCapture2;
    ThreadUploadPUMP1 threadUploadPUMP1;
    ThreadUploadPUMP2 threadUploadPUMP2;
    ThreadUploadPUMP3 threadUploadPUMP3;
    ThreadUploadPUMP4 threadUploadPUMP4;

    getPUMP1fromLocal getpump1fromlocal;
    getPUMP1fromYeelink getpump1fromyeelink;
    getPUMP2fromLocal getpump2fromlocal;
    getPUMP2fromYeelink getpump2fromyeelink;
    getPUMP3fromLocal getpump3fromlocal;
    getPUMP3fromYeelink getpump3fromyeelink;
    getPUMP4fromLocal getpump4fromlocal;
    getPUMP4fromYeelink getpump4fromyeelink;
    getCapture1fromLocal getcapture1fromlocal;
    getCapture2fromLocal getcapture2fromlocal;
    getCapture1fromYeelink getcapture1fromyeelink;
    getCapture2fromYeelink getcapture2fromyeelink;
};

#endif // MAINWINDOW_H
