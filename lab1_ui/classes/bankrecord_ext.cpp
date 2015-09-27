#include "bankrecord_ext.h"
#include <fstream>

void bankRecord_ext::setCountry(const QString &country) {
    this->country = country;
}

void bankRecord_ext::setCurrency(const QString &currency) {
    this->currency = currency;
}

QString bankRecord_ext::getCountry() const {
    return country;
}
QString bankRecord_ext::getCurrency() const {
    return currency;
}

string bankRecord_ext::toString() const {
    ostringstream strStream;
    strStream << "Record ID:  " << ID << endl;
    strStream << "  Summ:     " << sum << endl;
    strStream << "  Sender:   " << sender << endl;
    strStream << "  Receiver: " << receiver << endl;
    strStream << "  DATE:     " << date.day() << "." << date.month() << "." << date.year() << endl;
    strStream << "  Country:  " << country.toStdString() << endl;
    strStream << "  Currency: " << currency.toStdString() << endl;
//    if (toFile) {
//        ofstream outfile_ext("../lab1_ui/bankRecord_ext" + to_string(ID) + ".txt");
//        outfile_ext << strStream.str();
//        outfile_ext.close();
//    }
    return strStream.str();
}

string bankRecord_ext::toFileString() const {
    ostringstream strStream;
    strStream << 1 << endl;
    strStream << sum << endl;
    strStream << sender << endl;
    strStream << receiver << endl;
    strStream << date.day() << "." << date.month() << "." << date.year() << endl;
    strStream << country.toStdString() << endl;
    strStream << currency.toStdString() << endl;
    return strStream.str();
}
