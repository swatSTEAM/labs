#ifndef CONSUMER_H
#define CONSUMER_H

#include <QMainWindow>
#include <QObject>
#include "mainwindow.h"
class consumer : public QObject {

    Q_OBJECT

public:
     consumer(binaryTree<bankRecord>* data, Ui::MainWindow *ui):
         data(data), ui(ui) {ID = ++id;}

public slots:
    void start();

signals:
    void finished();
    void updateUI();

private:
    int ID;
    static int id;
    binaryTree<bankRecord>* data;
    Ui::MainWindow *ui;
};
#endif // CONSUMER_H
