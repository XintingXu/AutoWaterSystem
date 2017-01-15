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
    void openButton_clicked();
    void closeButton_clicked();
    void on_textBrowser_textChanged();

private:
    Ui::MainWindow *ui;
    QPushButton *button;
    QPushButton *button_close;
    QTextBrowser *textBrowser;
    QLabel *label_capture1;
    QLabel *label_capture2;

    CapturePI capturePI;
    CaptureUSB captureUSB;
    SrunLogIn srunLog;
};

#endif // MAINWINDOW_H
