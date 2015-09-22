#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "classes/bankrecord.h"
#include "classes/binarytree.h"
#include "classes/bankrecord_ext.h"
#include <iostream>
#include <string.h>
#include <QString>
#include <QDebug>
#include <QDate>
#include <QSignalMapper>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);


    ui->dateEdit->setMinimumDate(QDate(1800,1,1));                                          //Устанавливаем ограничение на дату
    ui->dateEdit->setMaximumDate(QDate(2077,1,1));                                          //
    ui->pushButton->setEnabled(false);                                                      //Дефолтный статус gui
    on_pushButton_2_clicked();
    tree = new binaryTree<bankRecord>();                                            //Создаём дерево
    ui->comboBox->addItems({"USA","Russia","China"});
    ui->comboBox_2->addItems({"$","rub","¥"});
    ui->comboBox->hide();
    ui->comboBox_2->hide();
    ui->label_7->hide();
    ui->label_8->hide();
}

MainWindow::~MainWindow() {                                                                 //Деструктор интерфейса
    delete ui;
}

void MainWindow::updateTreeCtrl() {                                                         //Функция обновление контрола дерева
    ui->listWidget->clear();                                                                //Отчищаем контрол дерева
    for (auto curr:tree->getContent()) {                                                    //Отображаем всё дерево заново
        ui->listWidget->addItem("#" + QString::number((*curr).getID()) + " Sum: " + QString::number((*curr).getSum(), 'f', 0) + (*curr).getCurrency());
    }
}

void MainWindow::on_pushButton_clicked() {                                                  //Хендлер на кнопку "Add" ("Change")
    QString sumstr = ui->lineEdit->text();                                                  //Собираем данные с полей
    ulong sum = sumstr.toULong();
    QString sender = ui->lineEdit_2->text();
    QString receiver = ui->lineEdit_3->text();
    QDate date = ui->dateEdit->date();
    QString country = ui->comboBox->currentText();
    QString currency = ui->comboBox_2->currentText();
    if (sender == "" || receiver == "") {                                                   //Проверка на корректность
        if (sender == "")
            ui->lineEdit_2->setStyleSheet("color: #b94a48;\
                                           background-color: #f2dede;");
        if (sender == "")
            ui->lineEdit_3->setStyleSheet("color: #b94a48;\
                                           background-color: #f2dede;");
        ui->label_9->setText("Invalid data");
    } else {
        if (change) {                                                                       //Изменение записи:
            int row = ui->listWidget->currentRow();
            if (row == -1) return;
                                                                                            //Удаляем текущую запись
            int id = (*(*tree)[row]).getID();
            tree->removeByID(id);
            //HERE
            if (ui->checkBox->isChecked()) {
                bankRecord_ext* record = new bankRecord_ext(id, sum, sender.toStdString(), receiver.toStdString(), date, country, currency);
                tree->insert(record);
            } else {
                bankRecord* record = new bankRecord(id, sum, sender.toStdString(), receiver.toStdString(), date);
                tree->insert(record);
            }
            this->updateTreeCtrl();                                                         //Обновляем интерфейс
            ui->listWidget->setCurrentRow(row);
            ui->label_9->setText("Record changed");
        } else {                                                                     //Создаём новую
            //HERE
            if (ui->checkBox->isChecked()) {
                bankRecord_ext* record = new bankRecord_ext(sum, sender.toStdString(), receiver.toStdString(), date, country, currency);
                tree->insert(record);
            } else {
                bankRecord* record = new bankRecord(sum, sender.toStdString(), receiver.toStdString(), date);
                tree->insert(record);
            }
            this->updateTreeCtrl();                                                         //Обновляем UI
            ui->label_9->setText("Record added");
        }
    }
}

void MainWindow::showExtCtrl() {
    ui->comboBox->show();
    ui->comboBox_2->show();
    ui->label_7->show();
    ui->label_8->show();
}

void MainWindow::hideExtCtrl() {
    ui->comboBox->hide();
    ui->comboBox_2->hide();
    ui->label_7->hide();
    ui->label_8->hide();
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item) {
    int row = ui->listWidget->currentRow();
    change = true;
    ui->pushButton->setText("Change");
    ui->pushButton_2->show();
    ui->pushButton_3->show();
    ui->label_6->show();
    ui->lineEdit_4->show();
    ui->label_9->setText("Record selected");
    //HERE
    bankRecord* currRec = (*tree)[row];
    ui->lineEdit_4->setText(QString::number((*currRec).getID()));
    ui->lineEdit->setText(QString::number((*currRec).getSum(), 'f', 0));
    ui->lineEdit_2->setText(QString::fromStdString((*currRec).getSender()));
    ui->lineEdit_3->setText(QString::fromStdString((*currRec).getReceiver()));
    ui->dateEdit->setDate((*currRec).getDate());
    if ((*currRec).isExtended()) {
        ui->comboBox->setCurrentText((*currRec).getCountry());
        ui->comboBox_2->setCurrentText((*currRec).getCurrency());
        ui->checkBox->setChecked(true);
        showExtCtrl();
    } else {
        ui->checkBox->setChecked(false);
        hideExtCtrl();
    }
}

//Кнопка new
void MainWindow::on_pushButton_2_clicked() {
    change = false;                         //Отчищаем поля
    ui->label_6->hide();
    ui->lineEdit_4->hide();
    ui->pushButton->setText("Add");
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->label_9->setText("Enter new record");
}

//Кнопка delete
void MainWindow::on_pushButton_3_clicked() {
    on_pushButton_2_clicked();
    int row = ui->listWidget->currentRow(); //Текущая запись
    int id = (*(*tree)[row]).getID();
    tree->removeByID(id);
    this->updateTreeCtrl();
    ui->label_9->setText("Record deleted");
}

//Хендлер для проверки на корректность
void MainWindow::on_lineEdit_textChanged(const QString &arg1) {
    ulong sum = arg1.toULong();
    if (sum == 0) {
        ui->lineEdit->setStyleSheet("color: #b94a48; background-color: #f2dede;");
        ui->pushButton->setEnabled(false);
        ui->label_9->setText("Invalid data");
    } else {
        ui->label_9->setText("All fine");
        ui->lineEdit->setStyleSheet("");
        ui->pushButton->setEnabled(true);
    }
}

//Поля вводе reciever
void MainWindow::on_lineEdit_2_textChanged(const QString &arg1) {
    ui->lineEdit_2->setStyleSheet("");
    ui->label_9->setText("All fine");
}

void MainWindow::on_lineEdit_3_textChanged(const QString &arg1) {
    ui->lineEdit_3->setStyleSheet("");
    ui->label_9->setText("All fine");
}


void MainWindow::on_checkBox_stateChanged(int arg1) {
    if (ui->checkBox->isChecked()) {
        showExtCtrl();
    } else {
        hideExtCtrl();
    }
}
