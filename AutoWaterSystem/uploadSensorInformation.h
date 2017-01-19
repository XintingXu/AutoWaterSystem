#ifndef UPLOADSENSORINFORMATION_H
#define UPLOADSENSORINFORMATION_H

#include <QThread>
#include <QString>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QImage>
#include <QProcess>

class ThreadUploadCapture1:public QThread{
    Q_OBJECT
private:
    QString cmdYeelink;
    QString cmdLocalHost;
    QProcess *pro;

public:
    ThreadUploadCapture1();
    ~ThreadUploadCapture1();
    void run();
signals:
    void threadLog(QString textMessage);
};

class ThreadUploadCapture2:public QThread{
    Q_OBJECT
private:
    QString cmdYeelink;
    QString cmdLocalHost;
    QProcess *pro;

public:
    ThreadUploadCapture2();
    ~ThreadUploadCapture2();
    void run();
signals:
    void threadLog(QString textMessage);
};

class ThreadUploadPUMP1:public QThread{
    Q_OBJECT
private:
    QString cmdBUMP1;
    QProcess *pro;
public:
    ThreadUploadPUMP1();
    ~ThreadUploadPUMP1();
    void run();
signals:
    void threadLog(QString textMessage);
};

class ThreadUploadPUMP2:public QThread{
    Q_OBJECT
private:
    QString cmdBUMP2;
    QProcess *pro;
public:
    ThreadUploadPUMP2();
    ~ThreadUploadPUMP2();
    void run();
signals:
    void threadLog(QString textMessage);
};

class ThreadUploadPUMP3:public QThread{
    Q_OBJECT
private:
    QString cmdBUMP3;
    QProcess *pro;
public:
    ThreadUploadPUMP3();
    ~ThreadUploadPUMP3();
    void run();
signals:
    void threadLog(QString textMessage);
};

class ThreadUploadPUMP4:public QThread{
    Q_OBJECT
private:
    QString cmdBUMP1;
    QProcess *pro;
public:
    ThreadUploadPUMP4();
    ~ThreadUploadPUMP4();
    void run();
signals:
    void threadLog(QString textMessage);
};

#endif // UPLOADSENSORINFORMATION_H
