#include <DeviceControl.h>
#include <mainwindow.h>

#include <QThread>
#include <QSemaphore>

#include <wiringPi.h>

extern bool RUNNING;

extern QSemaphore QSemaphore_openPump1;
extern QSemaphore QSemaphore_openPump2;
extern QSemaphore QSemaphore_openPump3;
extern QSemaphore QSemaphore_openPump4;

extern bool PUMP1_open,PUMP2_open,PUMP3_open,PUMP4_open,KEY1_press,KEY2_press,LQ1_high,LQ2_high;

ThreadControlPump1::ThreadControlPump1():QThread(){
    digitalWrite(PIN_CONTROL1,HIGH);
    digitalWrite(PIN_TRAN3,HIGH);
}

ThreadControlPump1::~ThreadControlPump1(){
    digitalWrite(PIN_CONTROL1,LOW);
    digitalWrite(PIN_TRAN3,HIGH);
}

void ThreadControlPump1::open(){
    digitalWrite(PIN_CONTROL1,LOW);
    digitalWrite(PIN_TRAN3,HIGH);
    digitalWrite(PIN_TRAN1,HIGH);
    digitalWrite(PIN_TRAN2,HIGH);
    digitalWrite(PIN_TRAN3,LOW);
    emit threadLog("PUMP1 opened.");
}

void ThreadControlPump1::close(){
    digitalWrite(PIN_CONTROL1,HIGH);
    digitalWrite(PIN_TRAN3,HIGH);
    emit threadLog("PUMP1 closed.");
}

void ThreadControlPump1::run(){
    while(RUNNING){
        QSemaphore_openPump1.acquire(1);

        if(!RUNNING)
            break;

        if(!PUMP1_open){
            close();
        }else{
            open();
            sleep(10000);
            close();
            for(int i = 0 ; i < QSemaphore_openPump1.available(); i++){
                QSemaphore_openPump1.acquire(1);
            }
        }
    }
}
