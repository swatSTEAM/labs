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
    bankRecord() = delete;
    //Стандартный конструктор
    bankRecord(const ulong &sum, const string &sender, const string &receiver, const QDate &date):
            sum(sum), sender(sender), receiver(receiver), date(date) {this->ID=++this->id;}
    //Конструктор для "изменения"
    bankRecord(const int &ID, const double &sum, const string &sender, const string &receiver, const QDate &date):
            ID(ID), sum(sum), sender(sender), receiver(receiver), date(date) {}
    bankRecord(const bankRecord&);
    //Set-методы
    bankRecord& setSum(const ulong sum);
    bankRecord& setSender(const string &sender);
    bankRecord& setReceiver(const string &receiver);
    bankRecord& setDate(const QDate &date);

    //Get-методы
    int getID() const;
    float getSum() const;
    QDate getDate() const;
    string getSender() const;
    string getReceiver() const;

    //Арифметические операторы
    inline bankRecord& operator+=(const ulong rhs);
    inline bankRecord& operator+=(const bankRecord& rhs);
    inline bankRecord& operator-=(const ulong rhs);
    inline bankRecord& operator-=(const bankRecord& rhs);
    inline bankRecord operator+(const bankRecord& rhs) const;
    inline bankRecord operator-(const bankRecord& rhs) const;

    inline bankRecord& operator++();
    inline bankRecord operator++(int);
    inline bankRecord& operator--();
    inline bankRecord operator--(int);

    //Операторы сравнения
    //Операторы сравнения
    friend inline bool operator==(const bankRecord& lhs, const bankRecord& rhs) {
        return (lhs.getSum()==rhs.getSum()&&
                lhs.getReceiver()==rhs.getReceiver()&&
                lhs.getSender()==rhs.getSender()&&
                lhs.getDate()==rhs.getDate()&&
                lhs.getCurrency()==rhs.getCurrency()&&
                lhs.getCountry()==rhs.getCountry());
    }
    friend inline bool operator< (const bankRecord& lhs, const bankRecord& rhs) {
        return (lhs.getSum()<rhs.getSum());
    }
    friend inline bool operator!=(const bankRecord& lhs, const bankRecord& rhs) {
        return !operator==(lhs,rhs);
    }
    friend inline bool operator> (const bankRecord& lhs, const bankRecord& rhs) {
        return  operator< (rhs,lhs);
    }
    friend inline bool operator<=(const bankRecord& lhs, const bankRecord& rhs) {
        return !operator> (lhs,rhs);
    }
    friend inline bool operator>=(const bankRecord& lhs, const bankRecord& rhs) {
        return !operator< (lhs,rhs);
    }


    //Логические операторы
    inline bool operator&&(const bankRecord& rhs);

    inline bool operator||(const bankRecord& rhs);
    //Присваивания
    inline bankRecord& operator=(bankRecord rhs);
    //Операторы приведения типа
    inline operator int();

    //Операторы вывода
    friend std::ostream& operator<<(std::ostream& os, const bankRecord& obj)
    {
        os << obj.toString();
        return os;
    }

    //Виртуальные методы
    virtual QString getCurrency() const;
    virtual QString getCountry() const;
    virtual string toString() const;
    virtual string toFileString() const;
    virtual ~bankRecord() {}
    virtual bool isExtended() const {
        return false;
    }
};

template<typename T1, typename T2>
ulong getRecordsSum(T1& lhs, T2& rhs) {
    return lhs.getSum()+rhs.getSum();
}

#endif // BANKRECORD_H
