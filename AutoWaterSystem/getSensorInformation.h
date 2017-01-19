#ifndef GETSENSORINFORMATION_H
#define GETSENSORINFORMATION_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QByteArray>
#include <QThread>
#include <QTime>

class getPUMP1fromLocal : public QThread{
    Q_OBJECT
private:
    const char * user_id = "100000000";
    const char *  user_pass = "f74507c134112393eb32fb9dc319064b7e0a03d0";
    QByteArray post_data;
    QNetworkAccessManager *manager;
    QNetworkRequest *request;
    QTime last_time;

public:
    void run();
    const char *  sensor_id = "200000001";
    int data_count;
    int start_position;
    getPUMP1fromLocal();
    ~getPUMP1fromLocal();

signals:
    void onFinished(QNetworkReply * reply);

private slots:
    void replyFinished(QNetworkReply * reply);
};

class getPUMP1fromYeelink : public QThread{
    Q_OBJECT
private:
    QByteArray post_data;
    QNetworkAccessManager *manager;
    QNetworkRequest *request;
    QTime last_time;
public:
    void run();
    getPUMP1fromYeelink();
    ~getPUMP1fromYeelink();

signals:
    void onFinished(QNetworkReply * reply);

private slots:
    void replyFinished(QNetworkReply * reply);
};



class getPUMP2fromLocal : public QThread{
    Q_OBJECT
private:
    const char * user_id = "100000000";
    const char *  user_pass = "f74507c134112393eb32fb9dc319064b7e0a03d0";
    QByteArray post_data;
    QNetworkAccessManager *manager;
    QNetworkRequest *request;
    QTime last_time;
public:
    void run();
    const char *  sensor_id = "200000002";
    int data_count;
    int start_position;
    getPUMP2fromLocal();
    ~getPUMP2fromLocal();

signals:
    void onFinished(QNetworkReply * reply);

private slots:
    void replyFinished(QNetworkReply * reply);
};

class getPUMP2fromYeelink : public QThread{
    Q_OBJECT
private:
    QByteArray post_data;
    QNetworkAccessManager *manager;
    QNetworkRequest *request;
    QTime last_time;
public:
    void run();
    getPUMP2fromYeelink();
    ~getPUMP2fromYeelink();

signals:
    void onFinished(QNetworkReply * reply);

private slots:
    void replyFinished(QNetworkReply * reply);
};



class getPUMP3fromLocal : public QThread{
    Q_OBJECT
private:
    const char * user_id = "100000000";
    const char *  user_pass = "f74507c134112393eb32fb9dc319064b7e0a03d0";
    QByteArray post_data;
    QNetworkAccessManager *manager;
    QNetworkRequest *request;
    QTime last_time;
public:
    void run();
    const char *  sensor_id = "200000003";
    int data_count;
    int start_position;
    getPUMP3fromLocal();
    ~getPUMP3fromLocal();

signals:
    void onFinished(QNetworkReply * reply);

private slots:
    void replyFinished(QNetworkReply * reply);
};

class getPUMP3fromYeelink : public QThread{
    Q_OBJECT
private:
    QByteArray post_data;
    QNetworkAccessManager *manager;
    QNetworkRequest *request;
    QTime last_time;
public:
    void run();
    getPUMP3fromYeelink();
    ~getPUMP3fromYeelink();

signals:
    void onFinished(QNetworkReply * reply);

private slots:
    void replyFinished(QNetworkReply * reply);
};




class getPUMP4fromLocal : public QThread{
    Q_OBJECT
private:
    const char * user_id = "100000000";
    const char *  user_pass = "f74507c134112393eb32fb9dc319064b7e0a03d0";
    QByteArray post_data;
    QNetworkAccessManager *manager;
    QNetworkRequest *request;
    QTime last_time;
public:
    void run();
    const char *  sensor_id = "200000004";
    int data_count;
    int start_position;
    getPUMP4fromLocal();
    ~getPUMP4fromLocal();

signals:
    void onFinished(QNetworkReply * reply);

private slots:
    void replyFinished(QNetworkReply * reply);
};

class getPUMP4fromYeelink : public QThread{
    Q_OBJECT
private:
    QByteArray post_data;
    QNetworkAccessManager *manager;
    QNetworkRequest *request;
    QTime last_time;
public:
    void run();
    getPUMP4fromYeelink();
    ~getPUMP4fromYeelink();

signals:
    void onFinished(QNetworkReply * reply);

private slots:
    void replyFinished(QNetworkReply * reply);
};



class getCapture1fromLocal : public QThread{
    Q_OBJECT
private:
    const char * user_id = "100000000";
    const char *  user_pass = "f74507c134112393eb32fb9dc319064b7e0a03d0";
    QByteArray post_data;
    QNetworkAccessManager *manager;
    QNetworkRequest *request;
    QTime last_time;
public:
    void run();
    const char *  sensor_id = "200000005";
    int data_count;
    int start_position;
    getCapture1fromLocal();
    ~getCapture1fromLocal();

signals:
    void onFinished(QNetworkReply * reply);

private slots:
    void replyFinished(QNetworkReply * reply);
};

class getCapture1fromYeelink : public QThread{
    Q_OBJECT
private:
    QByteArray post_data;
    QNetworkAccessManager *manager;
    QNetworkRequest *request;
    QTime last_time;
public:
    void run();
    getCapture1fromYeelink();
    ~getCapture1fromYeelink();

signals:
    void onFinished(QNetworkReply * reply);

private slots:
    void replyFinished(QNetworkReply * reply);
};



class getCapture2fromLocal : public QThread{
    Q_OBJECT
private:
    const char * user_id = "100000000";
    const char *  user_pass = "f74507c134112393eb32fb9dc319064b7e0a03d0";
    QByteArray post_data;
    QNetworkAccessManager *manager;
    QNetworkRequest *request;
    QTime last_time;
public:
    void run();
    const char *  sensor_id = "200000006";
    int data_count;
    int start_position;
    getCapture2fromLocal();
    ~getCapture2fromLocal();

signals:
    void onFinished(QNetworkReply * reply);

private slots:
    void replyFinished(QNetworkReply * reply);
};

class getCapture2fromYeelink : public QThread{
    Q_OBJECT
private:
    QByteArray post_data;
    QNetworkAccessManager *manager;
    QNetworkRequest *request;
    QTime last_time;
public:
    void run();
    getCapture2fromYeelink();
    ~getCapture2fromYeelink();

signals:
    void onFinished(QNetworkReply * reply);

private slots:
    void replyFinished(QNetworkReply * reply);
};

#endif // GETSENSORINFORMATION_H
