#include "NetworkOperation.h"


#include <QProcess>
#include <QThread>
#include <QSemaphore>
#include <QTime>
#include <QtNetwork>
#include <iostream>
#include <QString>

using namespace std;

extern bool RUNNING;

extern QSemaphore *Qsemphere_login;

SrunLogIn::SrunLogIn():QThread(){
    poc = new QProcess();
    curl = "/home/pi/login.sh";//the .sh file path
}

SrunLogIn::~SrunLogIn(){
    delete(poc);
}

void SrunLogIn::run(){
    while(RUNNING){
        Qsemphere_login->acquire(1);

        if(!RUNNING)
            break;

        QString info = "login.sh results : ";
        info.append(QString::number(poc->execute(curl)));//execute the .sh to complish curl function and show the curl result to the textBrowser
        emit threadLog(info);
    }
}

void SrunLogIn::stopLog(){
    emit threadLog(QString("Cannot connect to Server."));
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach(QHostAddress address,list){//check each ip address
        QString ip;
        if(address.protocol() == QAbstractSocket::IPv4Protocol){
            ip = "IP address = ";
            ip.append(address.toString());
            emit threadLog(ip);
        }
    }
}


ThreadGET::ThreadGET():QThread(){
    request = new QNetworkRequest;
}

ThreadGET::~ThreadGET(){
    delete(request);
}

void ThreadGET::run(){
    ;
}

ThreadPOST::ThreadPOST():QThread(){
    request = new QNetworkRequest;
}

ThreadPOST::~ThreadPOST(){
    delete(request);
}

void ThreadPOST::run(){
    while(RUNNING){
        QSemaphore_post.acquire(1);

        if(!RUNNING)
            break;

        request->setUrl(URL);
    }
}
