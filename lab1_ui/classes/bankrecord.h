//Класс bankRecord

#ifndef BANKRECORD_H
#define BANKRECORD_H

#include <iostream>
#include <string>
#include <sstream>
#include <QDate>
using namespace std;

class bankRecord {
protected:
    int ID;         //Уникальный идентификатор
    static int id;  //Идентификатор для текущего количество объектов
    ulong sum;
    string sender;
    string receiver;
    QDate date;
public:
    bankRecord() {}
    //Стандартный конструктор
    bankRecord(const ulong &sum, const string &sender, const string &receiver, const QDate &date):
            sum(sum), sender(sender), receiver(receiver), date(date) {this->ID=++this->id;}
    //Конструктор для "изменения"
    bankRecord(const int &ID, const double &sum, const string &sender, const string &receiver, const QDate &date):
            ID(ID), sum(sum), sender(sender), receiver(receiver), date(date) {}
    //Set-методы
    bankRecord& setSum(double sum);
    bankRecord* setSender(string sender);
    bankRecord* setReceiver(string receiver);
    bankRecord& setDate(QDate date);

    //Get-методы
    int getID();
    float getSum() const;
    QDate getDate();
    string getSender();
    string getReceiver();

    virtual string toString(bool toFile);
    ~bankRecord() {}
};

#endif // BANKRECORD_H
