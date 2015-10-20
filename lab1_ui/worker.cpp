#include "worker.h"
#include <QThread>
#include <QDebug>
#include "ui_mainwindow.h"

int worker::id = 0;

void worker::startWork() {
    while (data->Work) {
        ulong sum = rand()% 1000 +1;
        QString sender = "WORKER " + QString::number(ID);
        QString receiver = "WORKER " + QString::number(ID);
        QDate date = ui->dateEdit->date();
        QString country = QStringList({"USA","Russia","China"})[rand()%3];
        QString currency = QStringList({"$","rub","¥"})[rand()%3];

        data->dataMutex.lock();
        if (rand()%2) {
            bankRecord_ext* record = new bankRecord_ext(sum, sender.toStdString(), receiver.toStdString(), date, country, currency);
            data->insert(record);
        } else {
            bankRecord* record = new bankRecord(sum, sender.toStdString(), receiver.toStdString(), date);
            data->insert(record);
        }
        emit updateUI();
        qDebug() << "WORKER THREAD" << ID << ": RECORD CREATED";
        data->dataMutex.unlock();
        QThread::sleep(5);
    }
    emit finished();
}


