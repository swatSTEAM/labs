#ifndef BANKRECORD_EXT_H
#define BANKRECORD_EXT_H
#include "classes/bankrecord.h"

class bankRecord_ext : public bankRecord {
    QString country;
    QString currency;
public:
//    static QStringList contries;
//    static QStringList currencies;
    bankRecord_ext() : bankRecord() {}
    //Стандартный конструктор
    bankRecord_ext(const ulong &sum, const string &sender, const string &receiver, const QDate &date, const QString &country, const QString &currency) :
        bankRecord(sum, sender, receiver, date), country(country), currency(currency) {}
    //Конструктор для "изменения"
    bankRecord_ext(const int &ID, const ulong &sum, const string &sender, const string &receiver, const QDate &date, const QString &country, const QString &currency) :
        bankRecord(ID, sum, sender, receiver, date), country(country), currency(currency) {}

    //Set-методы
    void setCountry(const QString &country);
    void setCurrency(const QString &currency);
    //Get-методы
    virtual QString getCountry() const;
    virtual QString getCurrency() const;
    virtual bool isExtended() {
        return true;
    }
};

//QStringList bankRecord_ext::contries = {"USA","Russia","China"};
//QStringList bankRecord_ext::currencies = {"$","rub","¥"};

#endif // BANKRECORD_EXT_H
