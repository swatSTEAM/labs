#ifndef BANKRECORD2_H
#define BANKRECORD2_H
#include "classes/bankrecord.h"

class bankRecord_extended : public bankRecord
{
//    QStringList countries = {"USA","Russia","China"};
//    QStringList currencies = {"$","rub","¥"};
    QString country;
    QString currency;
public:
    bankRecord_extended(const ulong &sum, const string &sender, const string &receiver, const QDate &date, const QString &country, const QString &currency):
            sum(sum), sender(sender), receiver(receiver), date(date), country(country), currency(currency){this->ID=++this->id;}
};

#endif // BANKRECORD2_H
