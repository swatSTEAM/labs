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
#include <QFile>
#include <QFileInfo>
#include <QCoreApplication>
#include <QTextStream>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->tableWidget->setColumnWidth(0,40);

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
    QHeaderView *header = ui->tableWidget->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow() {                                                                 //Деструктор интерфейса
    delete ui;
}

void MainWindow::updateTreeCtrl() {                                                         //Функция обновление контрола дерева
    ui->tableWidget->clearContents();
    int row = 0;
    for (auto curr:tree->getContent()) {
         ui->tableWidget->removeRow(row);
         ui->tableWidget->insertRow(row);

         QTableWidgetItem* uiRec_id = new QTableWidgetItem;
         uiRec_id->setText(QString::number((*curr).getID()));
         ui->tableWidget->setItem(row, 0, uiRec_id);

         QTableWidgetItem* uiRec_sum = new QTableWidgetItem;
         uiRec_sum->setText(QString::number((*curr).getSum(), 'f', 0) + (*curr).getCurrency());
         ui->tableWidget->setItem(row, 1, uiRec_sum);

         QTableWidgetItem* uiRec_sender = new QTableWidgetItem;
         uiRec_sender->setText(QString::fromStdString((*curr).getSender()));
         ui->tableWidget->setItem(row, 2, uiRec_sender);

         QTableWidgetItem* uiRec_receiver = new QTableWidgetItem;
         uiRec_receiver->setText(QString::fromStdString((*curr).getReceiver()));
         ui->tableWidget->setItem(row++, 3, uiRec_receiver);
    }
    ui->tableWidget->setColumnWidth(0,40);
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
            int row = ui->tableWidget->currentRow();
            if (row == -1) return;
                                                                                            //Удаляем текущую запись
            int id = (*tree)[row].getID();
            tree->removeByID(id);
            //HERE
            if (ui->checkBox->isChecked()) {
                bankRecord_ext* record = new bankRecord_ext(id, sum, sender.toStdString(), receiver.toStdString(), date, country, currency);
                tree->insert(record);
            } else {
                bankRecord* record = new bankRecord(id, sum, sender.toStdString(), receiver.toStdString(), date);
                tree->insert(record);
            }
            updateTreeCtrl();                                                         //Обновляем интерфейс
            ui->tableWidget->setCurrentCell(row,0);
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
            updateTreeCtrl();                                                         //Обновляем UI
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

//Клик по таблице
void MainWindow::on_tableWidget_itemClicked() {
    int row = ui->tableWidget->currentRow();
    ui->tableWidget->setRangeSelected(QTableWidgetSelectionRange(row,0,row,3),true);
    change = true;
    ui->pushButton->setText("Change");
    ui->pushButton_2->show();
    ui->pushButton_3->show();
    ui->label_6->show();
    ui->lineEdit_4->show();
    ui->label_9->setText("Record selected");
    //HERE
    bankRecord& currRec = (*tree)[row];
    ui->lineEdit_4->setText(QString::number((currRec).getID()));
    ui->lineEdit->setText(QString::number((currRec).getSum(), 'f', 0));
    ui->lineEdit_2->setText(QString::fromStdString((currRec).getSender()));
    ui->lineEdit_3->setText(QString::fromStdString((currRec).getReceiver()));
    ui->dateEdit->setDate((currRec).getDate());
    if ((currRec).isExtended()) {
        ui->comboBox->setCurrentText((currRec).getCountry());
        ui->comboBox_2->setCurrentText((currRec).getCurrency());
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
    int row = ui->tableWidget->currentRow(); //Текущая запись
    int id = (*tree)[row].getID();
    tree->removeByID(id);
    ui->tableWidget->removeRow(row);
    updateTreeCtrl();
    ui->label_9->setText("Record deleted");
    on_pushButton_2_clicked();
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
void MainWindow::on_lineEdit_2_textChanged() {
    ui->lineEdit_2->setStyleSheet("");
    ui->label_9->setText("All fine");
}

void MainWindow::on_lineEdit_3_textChanged() {
    ui->lineEdit_3->setStyleSheet("");
    ui->label_9->setText("All fine");
}


void MainWindow::on_checkBox_stateChanged() {
    if (ui->checkBox->isChecked()) {
        showExtCtrl();
    } else {
        hideExtCtrl();
    }
}


void MainWindow::on_tableWidget_itemSelectionChanged()
{
//    on_tableWidget_itemClicked();
}

//Запись в файл
void MainWindow::on_pushButton_4_clicked()
{
    QString filename = "../lab1_ui/tree_out.txt";
    QFile out(filename);
    if (out.open(QIODevice::ReadWrite)) {
        QTextStream stream(&out);
        for (auto curr:tree->getContent()) {
            stream << QString::fromStdString(curr->toFileString());
        }
        out.resize(out.pos());
        QMessageBox::information(this, "File saved", "Tree saved to file " + QFileInfo(out).absoluteFilePath());
    } else {
        qDebug() << "Error";
    }
}

//Чтение из файла
void MainWindow::on_pushButton_5_clicked()
{
    tree->getContent().clear();
    QString filename = "../lab1_ui/tree_out.txt";
    QFile out(filename);
    if (out.open(QIODevice::ReadWrite)) {
        bool isExt = false;
        ulong sum;
        string sender;
        string receiver;
        QDate date;
        QTextStream stream(&out);
        enum Lines {
            extL, sumL, senderL, recieverL, dateL
        };

        while(!stream.atEnd()) {
            for (int i=0;i<=4;i++) {
                QString line = out.readLine().trimmed();
                switch (i) {
                    case (Lines::extL):
                        if (line == "1")
                            isExt = true;
                        break;
                    case (Lines::sumL):
                        sum = line.toULong();
                        break;
                    case (Lines::senderL):
                        sender = line.toStdString();
                        break;
                    case (Lines::recieverL):
                        receiver = line.toStdString();
                        break;
                    case (Lines::dateL):
                        QStringList fields = line.split(".");
                        date = QDate(fields[2].toInt(),fields[1].toInt(),fields[0].toInt());
                        break;
                }
            }

            if (isExt) {
                QString country = out.readLine().trimmed();
                QString currency = out.readLine().trimmed();
                bankRecord* record = new bankRecord_ext(sum, sender, receiver, date, country, currency);
                tree->insert(record);
                updateTreeCtrl();
            } else {
                bankRecord* record = new bankRecord(sum, sender, receiver, date);
                tree->insert(record);
                updateTreeCtrl();
            }
            isExt = false;
        }
        QMessageBox::information(this, "File was load", "New records was load from file " + QFileInfo(out).absoluteFilePath());
    } else {
        qDebug() << "Error";
    }
}
