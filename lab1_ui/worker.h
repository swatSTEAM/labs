#ifndef WORKER_H
#define WORKER_H
#include <QMainWindow>
#include <QObject>
#include "mainwindow.h"
class worker : public QObject {

    Q_OBJECT

public:
     worker(binaryTree<bankRecord>* data, Ui::MainWindow *ui):
         data(data), ui(ui) {ID = ++id;}

public slots:
    void startWork();

signals:
    void finished();
    void updateUI();

private:
    int ID;
    static int id;
    binaryTree<bankRecord>* data;
    Ui::MainWindow *ui;
};

#endif // WORKER_H
