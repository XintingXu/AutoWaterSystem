#ifndef DEVICECONTROL_H
#define DEVICECONTROL_H

#include <wiringPi.h>
#include <QSemaphore>
#include <QThread>

extern bool RUNNING;

extern QSemaphore QSemaphore_openPump1;
extern QSemaphore QSemaphore_openPump2;
extern QSemaphore QSemaphore_openPump3;
extern QSemaphore QSemaphore_openPump4;

extern bool PUMP1_open,PUMP2_open,PUMP3_open,PUMP4_open,KEY1_press,KEY2_press,LQ1_high,LQ2_high;

class ThreadControlPump1:public QThread{
    Q_OBJECT
private:
    open();
    close();

public:
    ThreadControlPump1();
    ~ThreadControlPump1();
    void run();

signals:
    void threadLog(QString textMessage);
};



class ThreadControlPump2:public QThread{
    Q_OBJECT
private:
    open();
    close();

public:
    ThreadControlPump2();
    ~ThreadControlPump2();
    void run();

signals:
    void threadLog(QString textMessage);
};


class ThreadControlPump3:public QThread{
    Q_OBJECT
private:
    open();
    close();

public:
    ThreadControlPump3();
    ~ThreadControlPump3();
    void run();

signals:
    void threadLog(QString textMessage);
};


class ThreadControlPump4:public QThread{
    Q_OBJECT
private:
    open();
    close();

public:
    ThreadControlPump4();
    ~ThreadControlPump4();
    void run();

signals:
    void threadLog(QString textMessage);
};

#endif // DEVICECONTROL_H
