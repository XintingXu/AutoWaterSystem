#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QImage>
#include <QWidget>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_openButton_clicked();
    void on_closeButton_clicked();

private:
    Ui::MainWindow *ui;
    QPushButton *button;
    QPushButton *button_close;
};

#endif // MAINWINDOW_H
