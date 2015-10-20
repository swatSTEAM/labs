#include "consumer.h"
#include <QThread>
#include <QDebug>
#include "ui_mainwindow.h"
int consumer::id = 0;

void consumer::start() {
    while (data->Consume) {
        data->dataMutex.lock();
        if (data->pop()) {
            qDebug() << "CONSUME THREAD" << ID << ": RECORD DELETED";
            emit updateUI();
        } else {
            qDebug() << "CONSUME THREAD" << ID << ": NO RECORDS";
        }

        data->dataMutex.unlock();
        QThread::sleep(5);
    }
    emit finished();
}
