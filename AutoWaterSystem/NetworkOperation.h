#ifndef NETWORKOPERATION_H
#define NETWORKOPERATION_H

#include <QProcess>
#include <QThread>
#include <QtNetwork>
#include <QString>

class SrunLogIn:public QThread{//login the Srun server to connect the internet
    Q_OBJECT
private:
    QProcess * poc;
    QString curl;

    void stopLog();//stop the log function and check ip info

public:
    SrunLogIn();
    ~SrunLogIn();
    void run();

signals:
    void threadLog(QString textMessage);
};

class ThreadPOST : public QThread{
    Q_OBJECT
private:
    QNetworkRequest * request;

public:
    QUrl URL;
    QString POSTData;
    QSemaphore QSemaphore_post;
    ThreadPOST();
    ~ThreadPOST();
    void run();

signals:
    void showResult(QString textMessage);
};

class ThreadGET : public QThread{
    Q_OBJECT
private:
    QNetworkRequest *request;
public:
    QUrl URL;
    QString user_id;
    QString user_key;

    QSemaphore *QSemaphore_get;
    ThreadGET();
    ~ThreadGET();
    void run();
signals:
    void threadLog(QString textMessage);
};

#endif // NETWORKOPERATION_H
