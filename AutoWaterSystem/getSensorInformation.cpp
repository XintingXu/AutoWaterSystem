#include <getSensorInformation.h>
#include <QSemaphore>
#include <QThread>
#include <iostream>
#include <QNetworkReply>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QTime>

using namespace std;

extern bool RUNNING;
extern bool PUMP1_open,PUMP2_open,PUMP3_open,PUMP4_open,KEY1_press,KEY2_press,LQ1_high,LQ2_high;
extern QSemaphore * QSemaphore_openPump1,*QSemaphore_openPump2,*QSemaphore_openPump3,*QSemaphore_openPump4;
extern QSemaphore *PICapture,*USBCapture;

getPUMP1fromLocal::getPUMP1fromLocal():QThread(){
    start_position = 0;
    data_count = 1;
    last_time = QTime::currentTime();
}

getPUMP1fromLocal::~getPUMP1fromLocal(){
    ;
}

void getPUMP1fromLocal::run(){
        manager = new QNetworkAccessManager();
        request = new QNetworkRequest();
        connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
        QString stringPost,stringGet;
        stringPost = stringPost.sprintf("user_id=%s&user_pass=%s",user_id,user_pass);
        post_data.append(stringPost);
        stringGet = stringGet.sprintf("http://localhost/AutoWaterSystem/downloadSensor12.php?sensor_id=%s&data_count=%d&start_position=%d",sensor_id,data_count,start_position);
        QUrl url(stringGet);
        request->setRawHeader("Content-Type","application/x-www-form-urlencoded");
        request->setHeader(QNetworkRequest::ContentLengthHeader,post_data.length());
        request->setUrl(url);

    while(RUNNING){
        manager->post(*request,post_data);
        this->exec();
        sleep(4);
    }
    delete(manager);
    delete(request);
}

void getPUMP1fromLocal::replyFinished(QNetworkReply *reply){
    if(reply->error() == QNetworkReply::NoError){
        QByteArray data = reply->readAll();
        QString result(data);
        cout << "result = " << result.toStdString() << endl;
        QJsonDocument document = QJsonDocument::fromJson(data);
        QJsonObject object = document.object();
        QJsonValue getDATA = object.value("DATA");
        QString Data = getDATA.toString();
        Data.remove(0,1);
        Data.remove(Data.length()-1,1);

        document = QJsonDocument::fromJson(Data.toLocal8Bit().data());
        object = document.object();
        QJsonValue realvalue = object.value("sensor_status");
        cout << "Read from JSON value = " << realvalue.toString().toStdString() << endl;
        if(realvalue.toString("0") == "1" && !PUMP1_open){
            QTime current = QTime::currentTime();
            if(current > last_time.addSecs(20)){
                last_time = current;
                PUMP1_open = true;
                if(QSemaphore_openPump1->available() == 0)
                    QSemaphore_openPump1->release(1);
            }
        }else if(realvalue.toString("0") == "0" && PUMP1_open){
            PUMP1_open = false;
            if(QSemaphore_openPump1->available() == 0)
                QSemaphore_openPump1->release(1);
        }

    }else{
        cout << "Internet Access Error" << endl;
    }
    this->quit();
}


getPUMP1fromYeelink::getPUMP1fromYeelink():QThread(){
    last_time = QTime::currentTime();
}

getPUMP1fromYeelink::~getPUMP1fromYeelink(){
    ;
}

void getPUMP1fromYeelink::run(){
        manager = new QNetworkAccessManager();
        request = new QNetworkRequest();
        connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
        QString stringGet;
        stringGet = "http://api.yeelink.net/v1.0/device/353664/sensor/398906/datapoints";
        QUrl url(stringGet);
        request->setRawHeader("Content-Type","application/x-www-form-urlencoded");
        request->setHeader(QNetworkRequest::ContentLengthHeader,post_data.length());
        request->setRawHeader("U-ApiKey","372ff6f73d10b192449d1c95dbaecff0");
        request->setUrl(url);

    while(RUNNING){
        manager->get(*request);
        this->exec();
        sleep(3);
    }
    delete(manager);
    delete(request);
}

void getPUMP1fromYeelink::replyFinished(QNetworkReply *reply){
    if(reply->error() == QNetworkReply::NoError){
        QByteArray data = reply->readAll();
        QString result(data);
        cout << "result = " << result.toStdString() << endl;
        QJsonDocument document = QJsonDocument::fromJson(data);
        QJsonObject object = document.object();
        QJsonValue value = object.value("value");
        cout << "Read from JSON value = " << value.toInt() << endl;
        if(value.toInt() == 1 && !PUMP1_open){
            QTime current = QTime::currentTime();
            if(current > last_time.addSecs(20)){
                last_time = current;
                PUMP1_open = true;
                if(QSemaphore_openPump1->available() == 0)
                    QSemaphore_openPump1->release(1);
            }
        }else if(value.toInt() == 0 && PUMP1_open){
            PUMP1_open = false;
            if(QSemaphore_openPump1->available() == 0)
                QSemaphore_openPump1->release(1);
        }
    }else{
        cout << "Internet Access Error" << endl;
    }
    this->quit();
}







getPUMP2fromLocal::getPUMP2fromLocal():QThread(){
    start_position = 0;
    data_count = 1;
    last_time = QTime::currentTime();
}

getPUMP2fromLocal::~getPUMP2fromLocal(){
    ;
}

void getPUMP2fromLocal::run(){
        manager = new QNetworkAccessManager();
        request = new QNetworkRequest();
        connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
        QString stringPost,stringGet;
        stringPost = stringPost.sprintf("user_id=%s&user_pass=%s",user_id,user_pass);
        post_data.append(stringPost);
        stringGet = stringGet.sprintf("http://localhost/AutoWaterSystem/downloadSensor12.php?sensor_id=%s&data_count=%d&start_position=%d",sensor_id,data_count,start_position);
        QUrl url(stringGet);
        request->setRawHeader("Content-Type","application/x-www-form-urlencoded");
        request->setHeader(QNetworkRequest::ContentLengthHeader,post_data.length());
        request->setUrl(url);

    while(RUNNING){
        manager->post(*request,post_data);
        this->exec();
        sleep(5);
    }
    delete(manager);
    delete(request);
}

void getPUMP2fromLocal::replyFinished(QNetworkReply *reply){
    if(reply->error() == QNetworkReply::NoError){
        QByteArray data = reply->readAll();
        QString result(data);
        cout << "result = " << result.toStdString() << endl;
        QJsonDocument document = QJsonDocument::fromJson(data);
        QJsonObject object = document.object();
        QJsonValue getDATA = object.value("DATA");
        QString Data = getDATA.toString();
        Data.remove(0,1);
        Data.remove(Data.length()-1,1);

        document = QJsonDocument::fromJson(Data.toLocal8Bit().data());
        object = document.object();
        QJsonValue realvalue = object.value("sensor_status");
        cout << "Read from JSON value = " << realvalue.toString().toStdString() << endl;
        if(realvalue.toString("0") == "1" && !PUMP2_open){
            QTime current = QTime::currentTime();
            if(current > last_time.addSecs(20)){
                last_time = current;
                PUMP2_open = true;
                if(QSemaphore_openPump2->available() == 0)
                    QSemaphore_openPump2->release(1);
            }
        }else if(realvalue.toString("0") == "0" && PUMP2_open){
            PUMP2_open = false;
            if(QSemaphore_openPump2->available() == 0)
                QSemaphore_openPump2->release(1);
        }

    }else{
        cout << "Internet Access Error" << endl;
    }
    this->quit();
}


getPUMP2fromYeelink::getPUMP2fromYeelink():QThread(){
    last_time = QTime::currentTime();
}

getPUMP2fromYeelink::~getPUMP2fromYeelink(){
    ;
}

void getPUMP2fromYeelink::run(){
        manager = new QNetworkAccessManager();
        request = new QNetworkRequest();
        connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
        QString stringGet;
        stringGet = "http://api.yeelink.net/v1.0/device/353664/sensor/398907/datapoints";
        QUrl url(stringGet);
        request->setRawHeader("Content-Type","application/x-www-form-urlencoded");
        request->setHeader(QNetworkRequest::ContentLengthHeader,post_data.length());
        request->setRawHeader("U-ApiKey","372ff6f73d10b192449d1c95dbaecff0");
        request->setUrl(url);

    while(RUNNING){
        manager->get(*request);
        this->exec();
        sleep(3);
    }
    delete(manager);
    delete(request);
}

void getPUMP2fromYeelink::replyFinished(QNetworkReply *reply){
    if(reply->error() == QNetworkReply::NoError){
        QByteArray data = reply->readAll();
        QString result(data);
        cout << "result = " << result.toStdString() << endl;
        QJsonDocument document = QJsonDocument::fromJson(data);
        QJsonObject object = document.object();
        QJsonValue value = object.value("value");
        cout << "Read from JSON value = " << value.toInt() << endl;
        if(value.toInt() == 1 && !PUMP2_open){
            QTime current = QTime::currentTime();
            if(current > last_time.addSecs(20)){
                last_time = current;
                PUMP2_open = true;
                if(QSemaphore_openPump2->available() == 0)
                    QSemaphore_openPump2->release(1);
            }
        }else if(value.toInt() == 0 && PUMP2_open){
            PUMP2_open = false;
            if(QSemaphore_openPump2->available() == 0)
                QSemaphore_openPump2->release(1);
        }
    }else{
        cout << "Internet Access Error" << endl;
    }
    this->quit();
}






getPUMP3fromLocal::getPUMP3fromLocal():QThread(){
    start_position = 0;
    data_count = 1;
    last_time = QTime::currentTime();
}

getPUMP3fromLocal::~getPUMP3fromLocal(){
    ;
}

void getPUMP3fromLocal::run(){
        manager = new QNetworkAccessManager();
        request = new QNetworkRequest();
        connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
        QString stringPost,stringGet;
        stringPost = stringPost.sprintf("user_id=%s&user_pass=%s",user_id,user_pass);
        post_data.append(stringPost);
        stringGet = stringGet.sprintf("http://localhost/AutoWaterSystem/downloadSensor12.php?sensor_id=%s&data_count=%d&start_position=%d",sensor_id,data_count,start_position);
        QUrl url(stringGet);
        request->setRawHeader("Content-Type","application/x-www-form-urlencoded");
        request->setHeader(QNetworkRequest::ContentLengthHeader,post_data.length());
        request->setUrl(url);

    while(RUNNING){
        manager->post(*request,post_data);
        this->exec();
        sleep(7);
    }
    delete(manager);
    delete(request);
}

void getPUMP3fromLocal::replyFinished(QNetworkReply *reply){
    if(reply->error() == QNetworkReply::NoError){
        QByteArray data = reply->readAll();
        QString result(data);
        cout << "result = " << result.toStdString() << endl;
        QJsonDocument document = QJsonDocument::fromJson(data);
        QJsonObject object = document.object();
        QJsonValue getDATA = object.value("DATA");
        QString Data = getDATA.toString();
        Data.remove(0,1);
        Data.remove(Data.length()-1,1);

        document = QJsonDocument::fromJson(Data.toLocal8Bit().data());
        object = document.object();
        QJsonValue realvalue = object.value("sensor_status");
        cout << "Read from JSON value = " << realvalue.toString().toStdString() << endl;
        if(realvalue.toString("0") == "1" && !PUMP3_open){
            QTime current = QTime::currentTime();
            if(current > last_time.addSecs(20)){
                last_time = current;
                PUMP3_open = true;
                if(QSemaphore_openPump3->available() == 0)
                    QSemaphore_openPump3->release(1);
            }
        }else if(realvalue.toString("0") == "0" && PUMP3_open){
            PUMP3_open = false;
            if(QSemaphore_openPump3->available() == 0)
                QSemaphore_openPump3->release(1);
        }

    }else{
        cout << "Internet Access Error" << endl;
    }
    this->quit();
}


getPUMP3fromYeelink::getPUMP3fromYeelink():QThread(){
    last_time = QTime::currentTime();
}

getPUMP3fromYeelink::~getPUMP3fromYeelink(){
    ;
}

void getPUMP3fromYeelink::run(){
        manager = new QNetworkAccessManager();
        request = new QNetworkRequest();
        connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
        QString stringGet;
        stringGet = "http://api.yeelink.net/v1.0/device/353664/sensor/398908/datapoints";
        QUrl url(stringGet);
        request->setRawHeader("Content-Type","application/x-www-form-urlencoded");
        request->setHeader(QNetworkRequest::ContentLengthHeader,post_data.length());
        request->setRawHeader("U-ApiKey","372ff6f73d10b192449d1c95dbaecff0");
        request->setUrl(url);

    while(RUNNING){
        manager->get(*request);
        this->exec();
        sleep(5);
    }
    delete(manager);
    delete(request);
}

void getPUMP3fromYeelink::replyFinished(QNetworkReply *reply){
    if(reply->error() == QNetworkReply::NoError){
        QByteArray data = reply->readAll();
        QString result(data);
        cout << "result = " << result.toStdString() << endl;
        QJsonDocument document = QJsonDocument::fromJson(data);
        QJsonObject object = document.object();
        QJsonValue value = object.value("value");
        cout << "Read from JSON value = " << value.toInt() << endl;
        if(value.toInt() == 1 && !PUMP3_open){
            QTime current = QTime::currentTime();
            if(current > last_time.addSecs(20)){
                last_time = current;
                PUMP3_open = true;
                if(QSemaphore_openPump3->available() == 0)
                    QSemaphore_openPump3->release(1);
            }
        }else if(value.toInt() == 0 && PUMP3_open){
            PUMP3_open = false;
            if(QSemaphore_openPump3->available() == 0)
                QSemaphore_openPump3->release(1);
        }
    }else{
        cout << "Internet Access Error" << endl;
    }
    this->quit();
}





getPUMP4fromLocal::getPUMP4fromLocal():QThread(){
    start_position = 0;
    data_count = 1;
    last_time = QTime::currentTime();
}

getPUMP4fromLocal::~getPUMP4fromLocal(){
    ;
}

void getPUMP4fromLocal::run(){
        manager = new QNetworkAccessManager();
        request = new QNetworkRequest();
        connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
        QString stringPost,stringGet;
        stringPost = stringPost.sprintf("user_id=%s&user_pass=%s",user_id,user_pass);
        post_data.append(stringPost);
        stringGet = stringGet.sprintf("http://localhost/AutoWaterSystem/downloadSensor12.php?sensor_id=%s&data_count=%d&start_position=%d",sensor_id,data_count,start_position);
        QUrl url(stringGet);
        request->setRawHeader("Content-Type","application/x-www-form-urlencoded");
        request->setHeader(QNetworkRequest::ContentLengthHeader,post_data.length());
        request->setUrl(url);

    while(RUNNING){
        manager->post(*request,post_data);
        this->exec();
        sleep(7);
    }
    delete(manager);
    delete(request);
}

void getPUMP4fromLocal::replyFinished(QNetworkReply *reply){
    if(reply->error() == QNetworkReply::NoError){
        QByteArray data = reply->readAll();
        QString result(data);
        cout << "result = " << result.toStdString() << endl;
        QJsonDocument document = QJsonDocument::fromJson(data);
        QJsonObject object = document.object();
        QJsonValue getDATA = object.value("DATA");
        QString Data = getDATA.toString();
        Data.remove(0,1);
        Data.remove(Data.length()-1,1);

        document = QJsonDocument::fromJson(Data.toLocal8Bit().data());
        object = document.object();
        QJsonValue realvalue = object.value("sensor_status");
        cout << "Read from JSON value = " << realvalue.toString().toStdString() << endl;
        if(realvalue.toString("0") == "1" && !PUMP4_open){
            QTime current = QTime::currentTime();
            if(current > last_time.addSecs(20)){
                last_time = current;
                PUMP4_open = true;
                if(QSemaphore_openPump4->available() == 0)
                    QSemaphore_openPump4->release(1);
            }
        }else if(realvalue.toString("0") == "0" && PUMP4_open){
            PUMP4_open = false;
            if(QSemaphore_openPump4->available() == 0)
                QSemaphore_openPump4->release(1);
        }

    }else{
        cout << "Internet Access Error" << endl;
    }
    this->quit();
}


getPUMP4fromYeelink::getPUMP4fromYeelink():QThread(){
    last_time = QTime::currentTime();
}

getPUMP4fromYeelink::~getPUMP4fromYeelink(){
    ;
}

void getPUMP4fromYeelink::run(){
        manager = new QNetworkAccessManager();
        request = new QNetworkRequest();
        connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
        QString stringGet;
        stringGet = "http://api.yeelink.net/v1.0/device/353664/sensor/398909/datapoints";
        QUrl url(stringGet);
        request->setRawHeader("Content-Type","application/x-www-form-urlencoded");
        request->setHeader(QNetworkRequest::ContentLengthHeader,post_data.length());
        request->setRawHeader("U-ApiKey","372ff6f73d10b192449d1c95dbaecff0");
        request->setUrl(url);

    while(RUNNING){
        manager->get(*request);
        this->exec();
        sleep(5);
    }
    delete(manager);
    delete(request);
}

void getPUMP4fromYeelink::replyFinished(QNetworkReply *reply){
    if(reply->error() == QNetworkReply::NoError){
        QByteArray data = reply->readAll();
        QString result(data);
        cout << "result = " << result.toStdString() << endl;
        QJsonDocument document = QJsonDocument::fromJson(data);
        QJsonObject object = document.object();
        QJsonValue value = object.value("value");
        cout << "Read from JSON value = " << value.toInt() << endl;
        if(value.toInt() == 1 && !PUMP4_open){
            QTime current = QTime::currentTime();
            if(current > last_time.addSecs(20)){
                last_time = current;
                PUMP4_open = true;
                if(QSemaphore_openPump4->available() == 0)
                    QSemaphore_openPump4->release(1);
            }
        }else if(value.toInt() == 0 && PUMP4_open){
            PUMP4_open = false;
            if(QSemaphore_openPump4->available() == 0)
                QSemaphore_openPump4->release(1);
        }
    }else{
        cout << "Internet Access Error" << endl;
    }
    this->quit();
}





getCapture1fromLocal::getCapture1fromLocal():QThread(){
    start_position = 0;
    data_count = 1;
    last_time = QTime::currentTime();
}

getCapture1fromLocal::~getCapture1fromLocal(){
    ;
}

void getCapture1fromLocal::run(){
        manager = new QNetworkAccessManager();
        request = new QNetworkRequest();
        connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
        QString stringPost,stringGet;
        stringPost = stringPost.sprintf("user_id=%s&user_pass=%s",user_id,user_pass);
        post_data.append(stringPost);
        stringGet = stringGet.sprintf("http://localhost/AutoWaterSystem/downloadSensor12.php?sensor_id=%s&data_count=%d&start_position=%d",sensor_id,data_count,start_position);
        QUrl url(stringGet);
        request->setRawHeader("Content-Type","application/x-www-form-urlencoded");
        request->setHeader(QNetworkRequest::ContentLengthHeader,post_data.length());
        request->setUrl(url);

    while(RUNNING){
        manager->post(*request,post_data);
        this->exec();
        sleep(5);
    }
    delete(manager);
    delete(request);
}

void getCapture1fromLocal::replyFinished(QNetworkReply *reply){
    if(reply->error() == QNetworkReply::NoError){
        QByteArray data = reply->readAll();
        QString result(data);
        cout << "result = " << result.toStdString() << endl;
        QJsonDocument document = QJsonDocument::fromJson(data);
        QJsonObject object = document.object();
        QJsonValue getDATA = object.value("DATA");
        QString Data = getDATA.toString();
        Data.remove(0,1);
        Data.remove(Data.length()-1,1);

        document = QJsonDocument::fromJson(Data.toLocal8Bit().data());
        object = document.object();
        QJsonValue realvalue = object.value("sensor_status");
        cout << "Read from JSON value = " << realvalue.toString().toStdString() << endl;
        if(realvalue.toString("0") == "1"){
            QTime current = QTime::currentTime();
            if(current > last_time.addSecs(10)){
                last_time = current;
                if(PICapture->available() == 0)
                    PICapture->release(1);
            }
        }

    }else{
        cout << "Internet Access Error" << endl;
    }
    this->quit();
}


getCapture1fromYeelink::getCapture1fromYeelink():QThread(){
    last_time = QTime::currentTime();
}

getCapture1fromYeelink::~getCapture1fromYeelink(){
    ;
}

void getCapture1fromYeelink::run(){
        manager = new QNetworkAccessManager();
        request = new QNetworkRequest();
        connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
        QString stringGet;
        stringGet = "http://api.yeelink.net/v1.0/device/353664/sensor/399676/datapoints";
        QUrl url(stringGet);
        request->setRawHeader("Content-Type","application/x-www-form-urlencoded");
        request->setHeader(QNetworkRequest::ContentLengthHeader,post_data.length());
        request->setRawHeader("U-ApiKey","372ff6f73d10b192449d1c95dbaecff0");
        request->setUrl(url);

    while(RUNNING){
        manager->get(*request);
        this->exec();
        sleep(4);
    }
    delete(manager);
    delete(request);
}

void getCapture1fromYeelink::replyFinished(QNetworkReply *reply){
    if(reply->error() == QNetworkReply::NoError){
        QByteArray data = reply->readAll();
        QString result(data);
        cout << "result = " << result.toStdString() << endl;
        QJsonDocument document = QJsonDocument::fromJson(data);
        QJsonObject object = document.object();
        QJsonValue value = object.value("value");
        cout << "Read from JSON value = " << value.toInt() << endl;
        if(value.toInt() == 1){
            QTime current = QTime::currentTime();
            if(current > last_time.addSecs(20)){
                last_time = current;
                if(PICapture->available() == 0)
                    PICapture->release(1);
            }
        }
    }else{
        cout << "Internet Access Error" << endl;
    }
    this->quit();
}







getCapture2fromLocal::getCapture2fromLocal():QThread(){
    start_position = 0;
    data_count = 1;
    last_time = QTime::currentTime();
}

getCapture2fromLocal::~getCapture2fromLocal(){
    ;
}

void getCapture2fromLocal::run(){
        manager = new QNetworkAccessManager();
        request = new QNetworkRequest();
        connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
        QString stringPost,stringGet;
        stringPost = stringPost.sprintf("user_id=%s&user_pass=%s",user_id,user_pass);
        post_data.append(stringPost);
        stringGet = stringGet.sprintf("http://localhost/AutoWaterSystem/downloadSensor12.php?sensor_id=%s&data_count=%d&start_position=%d",sensor_id,data_count,start_position);
        QUrl url(stringGet);
        request->setRawHeader("Content-Type","application/x-www-form-urlencoded");
        request->setHeader(QNetworkRequest::ContentLengthHeader,post_data.length());
        request->setUrl(url);

    while(RUNNING){
        manager->post(*request,post_data);
        this->exec();
        sleep(5);
    }
    delete(manager);
    delete(request);
}

void getCapture2fromLocal::replyFinished(QNetworkReply *reply){
    if(reply->error() == QNetworkReply::NoError){
        QByteArray data = reply->readAll();
        QString result(data);
        cout << "result = " << result.toStdString() << endl;
        QJsonDocument document = QJsonDocument::fromJson(data);
        QJsonObject object = document.object();
        QJsonValue getDATA = object.value("DATA");
        QString Data = getDATA.toString();
        Data.remove(0,1);
        Data.remove(Data.length()-1,1);

        document = QJsonDocument::fromJson(Data.toLocal8Bit().data());
        object = document.object();
        QJsonValue realvalue = object.value("sensor_status");
        cout << "Read from JSON value = " << realvalue.toString().toStdString() << endl;
        if(realvalue.toString("0") == "1"){
            QTime current = QTime::currentTime();
            if(current > last_time.addSecs(10)){
                last_time = current;
                if(USBCapture->available() == 0)
                    USBCapture->release(1);
            }
        }

    }else{
        cout << "Internet Access Error" << endl;
    }
    this->quit();
}


getCapture2fromYeelink::getCapture2fromYeelink():QThread(){
    last_time = QTime::currentTime();
}

getCapture2fromYeelink::~getCapture2fromYeelink(){
    ;
}

void getCapture2fromYeelink::run(){
        manager = new QNetworkAccessManager();
        request = new QNetworkRequest();
        connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
        QString stringGet;
        stringGet = "http://api.yeelink.net/v1.0/device/353664/sensor/399677/datapoints";
        QUrl url(stringGet);
        request->setRawHeader("Content-Type","application/x-www-form-urlencoded");
        request->setHeader(QNetworkRequest::ContentLengthHeader,post_data.length());
        request->setRawHeader("U-ApiKey","372ff6f73d10b192449d1c95dbaecff0");
        request->setUrl(url);

    while(RUNNING){
        manager->get(*request);
        this->exec();
        sleep(4);
    }
    delete(manager);
    delete(request);
}

void getCapture2fromYeelink::replyFinished(QNetworkReply *reply){
    if(reply->error() == QNetworkReply::NoError){
        QByteArray data = reply->readAll();
        QString result(data);
        cout << "result = " << result.toStdString() << endl;
        QJsonDocument document = QJsonDocument::fromJson(data);
        QJsonObject object = document.object();
        QJsonValue value = object.value("value");
        cout << "Read from JSON value = " << value.toInt() << endl;
        if(value.toInt() == 1){
            QTime current = QTime::currentTime();
            if(current > last_time.addSecs(20)){
                last_time = current;
                if(USBCapture->available() == 0)
                    USBCapture->release(1);
            }
        }
    }else{
        cout << "Internet Access Error" << endl;
    }
    this->quit();
}
