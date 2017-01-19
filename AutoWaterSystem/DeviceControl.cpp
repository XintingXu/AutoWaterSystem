#include <DeviceControl.h>
#include <mainwindow.h>

#include <QThread>
#include <QSemaphore>

#include <wiringPi.h>

extern bool RUNNING;

extern QSemaphore *QSemaphore_openPump1;
extern QSemaphore *QSemaphore_openPump2;
extern QSemaphore *QSemaphore_openPump3;
extern QSemaphore *QSemaphore_openPump4;

extern bool PUMP1_open,PUMP2_open,PUMP3_open,PUMP4_open,KEY1_press,KEY2_press,LQ1_high,LQ2_high;
extern QSemaphore * QSemaphore_openPump1_done,* QSemaphore_openPump2_done, * QSemaphore_openPump3_done,*QSemaphore_openPump4_done;

ThreadControlPump1::ThreadControlPump1():QThread(){
    digitalWrite(PIN_CONTROL1,HIGH);
    digitalWrite(PIN_TRAN3,HIGH);
}

ThreadControlPump1::~ThreadControlPump1(){
    digitalWrite(PIN_CONTROL1,HIGH);
    digitalWrite(PIN_TRAN3,HIGH);
}

void ThreadControlPump1::open(){
    PUMP1_open = true;
    digitalWrite(PIN_CONTROL1,LOW);
    digitalWrite(PIN_TRAN3,HIGH);
    digitalWrite(PIN_TRAN1,HIGH);
    digitalWrite(PIN_TRAN2,HIGH);
    digitalWrite(PIN_TRAN3,LOW);
    emit threadLog("PUMP1 opened.");
    QSemaphore_openPump1_done->acquire(QSemaphore_openPump1_done->available());
    QSemaphore_openPump1_done->release(1);
}

void ThreadControlPump1::close(){
    PUMP1_open = false;
    digitalWrite(PIN_CONTROL1,HIGH);
    digitalWrite(PIN_TRAN3,HIGH);
    emit threadLog("PUMP1 closed.");
    QSemaphore_openPump1_done->acquire(QSemaphore_openPump1_done->available());
    QSemaphore_openPump1_done->release(1);
}

void ThreadControlPump1::run(){
    while(RUNNING){
        QSemaphore_openPump1->acquire(1);

        if(!RUNNING){
            QSemaphore_openPump1_done->release(1);
            break;
        }

        if(!PUMP1_open){
            close();
        }else{
            open();
            sleep(15);
            close();
            for(int i = 0 ; i < QSemaphore_openPump1->available(); i++){
                QSemaphore_openPump1->acquire(1);
            }
        }
    }
}



ThreadControlPump2::ThreadControlPump2():QThread(){
    digitalWrite(PIN_CONTROL2,HIGH);
    digitalWrite(PIN_TRAN3,HIGH);
}

ThreadControlPump2::~ThreadControlPump2(){
    digitalWrite(PIN_CONTROL2,HIGH);
    digitalWrite(PIN_TRAN3,HIGH);
}

void ThreadControlPump2::open(){
    PUMP2_open = true;
    digitalWrite(PIN_CONTROL2,LOW);
    digitalWrite(PIN_TRAN3,HIGH);
    digitalWrite(PIN_TRAN1,HIGH);
    digitalWrite(PIN_TRAN2,LOW);
    digitalWrite(PIN_TRAN3,LOW);
    emit threadLog("PUMP2 opened.");
    QSemaphore_openPump2_done->acquire(QSemaphore_openPump2_done->available());
    QSemaphore_openPump2_done->release(1);
}

void ThreadControlPump2::close(){
    PUMP2_open = false;
    digitalWrite(PIN_CONTROL2,HIGH);
    digitalWrite(PIN_TRAN3,HIGH);
    emit threadLog("PUMP2 closed.");
    sleep(10);
    QSemaphore_openPump2_done->acquire(QSemaphore_openPump2_done->available());
    QSemaphore_openPump2_done->release(1);
}

void ThreadControlPump2::run(){
    while(RUNNING){
        QSemaphore_openPump2->acquire(1);

        if(!RUNNING){
            QSemaphore_openPump2_done->release(1);
            break;
        }

        if(!PUMP2_open){
            close();
        }else{
            open();
            sleep(5);
            close();

            QSemaphore_openPump2->acquire(QSemaphore_openPump2->available());
        }
    }
}


ThreadControlPump3::ThreadControlPump3():QThread(){
    digitalWrite(PIN_CONTROL3,HIGH);
    digitalWrite(PIN_TRAN3,HIGH);
}

ThreadControlPump3::~ThreadControlPump3(){
    digitalWrite(PIN_CONTROL3,HIGH);
    digitalWrite(PIN_TRAN3,HIGH);
}

void ThreadControlPump3::open(){
    PUMP3_open = true;
    digitalWrite(PIN_CONTROL3,LOW);
    digitalWrite(PIN_TRAN3,HIGH);
    digitalWrite(PIN_TRAN1,LOW);
    digitalWrite(PIN_TRAN2,HIGH);
    digitalWrite(PIN_TRAN3,LOW);
    emit threadLog("PUMP3 opened.");
    QSemaphore_openPump3_done->acquire(QSemaphore_openPump3_done->available());
    QSemaphore_openPump3_done->release(1);
}

void ThreadControlPump3::close(){
    PUMP3_open = false;
    digitalWrite(PIN_CONTROL3,HIGH);
    digitalWrite(PIN_TRAN3,HIGH);
    emit threadLog("PUMP3 closed.");
    QSemaphore_openPump3_done->acquire(QSemaphore_openPump3_done->available());
    QSemaphore_openPump3_done->release(1);
}

void ThreadControlPump3::run(){
    while(RUNNING){
        QSemaphore_openPump3->acquire(1);

        if(!RUNNING){
            QSemaphore_openPump3_done->release(1);
            break;
        }

        if(!PUMP3_open){
            close();
        }else{
            open();
            sleep(15);
            close();
            for(int i = 0 ; i < QSemaphore_openPump3->available(); i++){
                QSemaphore_openPump3->acquire(1);
            }
        }
    }
}


ThreadControlPump4::ThreadControlPump4():QThread(){
    digitalWrite(PIN_CONTROL4,HIGH);
    digitalWrite(PIN_TRAN3,HIGH);
}

ThreadControlPump4::~ThreadControlPump4(){
    digitalWrite(PIN_CONTROL4,HIGH);
    digitalWrite(PIN_TRAN3,HIGH);
}

void ThreadControlPump4::open(){
    PUMP4_open = true;
    digitalWrite(PIN_CONTROL4,LOW);
    digitalWrite(PIN_TRAN3,HIGH);
    digitalWrite(PIN_TRAN1,LOW);
    digitalWrite(PIN_TRAN2,LOW);
    digitalWrite(PIN_TRAN3,LOW);
    emit threadLog("PUMP4 opened.");
    QSemaphore_openPump4_done->acquire(QSemaphore_openPump4_done->available());
    QSemaphore_openPump4_done->release(1);
}

void ThreadControlPump4::close(){
    PUMP4_open = false;
    digitalWrite(PIN_CONTROL4,HIGH);
    digitalWrite(PIN_TRAN3,HIGH);
    emit threadLog("PUMP4 closed.");
    QSemaphore_openPump4_done->acquire(QSemaphore_openPump4_done->available());
    QSemaphore_openPump4_done->release(1);
}

void ThreadControlPump4::run(){
    while(RUNNING){
        QSemaphore_openPump4->acquire(1);

        if(!RUNNING){
            QSemaphore_openPump4_done->release(1);
            break;
        }

        if(!PUMP4_open){
            close();
        }else{
            open();
            sleep(15);
            close();
            for(int i = 0 ; i < QSemaphore_openPump4->available(); i++){
                QSemaphore_openPump4->acquire(1);
            }
        }
    }
}
