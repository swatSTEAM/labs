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

    virtual bool isExtended() const {
        return false;
    }
    //Арифметические операторы

    inline bankRecord operator+=(const ulong rhs)
    {
      sum+=rhs;
      return *this;
    }

    inline bankRecord operator+=(const bankRecord& rhs)
    {
      sum+=rhs.getSum();
      return *this;
    }

    inline ulong operator+(const bankRecord& rhs)
    {

      return ((this->getSum())+rhs.getSum());
    }

    //Операторы сравнения
    friend inline bool operator==(const bankRecord& lhs, const bankRecord& rhs) {
        return (lhs.getSum()==rhs.getSum()&&
                lhs.getReceiver()==rhs.getReceiver()&&
                lhs.getSender()==rhs.getSender()&&
                lhs.getDate()==rhs.getDate()&&
                lhs.getCurrency()==rhs.getCurrency()&&
                lhs.getCountry()==rhs.getCountry());
    }

    friend inline bool operator< (const bankRecord& lhs, const bankRecord& rhs){return (lhs.getSum()<rhs.getSum());}
    friend inline bool operator!=(const bankRecord& lhs, const bankRecord& rhs){return !operator==(lhs,rhs);}
    friend inline bool operator> (const bankRecord& lhs, const bankRecord& rhs){return  operator< (rhs,lhs);}
    friend inline bool operator<=(const bankRecord& lhs, const bankRecord& rhs){return !operator> (lhs,rhs);}
    friend inline bool operator>=(const bankRecord& lhs, const bankRecord& rhs){return !operator< (lhs,rhs);}


    virtual QString getCurrency() const;
    virtual QString getCountry() const;
    virtual string toString() const;
    virtual string toFileString() const;
    virtual ~bankRecord() {}


   //Операторы вывода
//    friend QDebug& operator<<(QDebug& os, const bankRecord& obj)
//    {
//      // write obj to stream
//      os << obj.toString();
//      return os;
//    }

    /*std::istream& operator>>(std::istream& is, bankRecord& obj)
    {
      // read obj from stream

      if(  no valid object of T found in stream  )
        is.setstate(std::ios::failbit);

      return is;
    }
    */
};

#endif // BANKRECORD_H
