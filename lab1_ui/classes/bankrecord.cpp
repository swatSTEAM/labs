#include "bankrecord.h"
#include <fstream>


using namespace std;

int bankRecord::id = 0;

/****************** set methods ******************/
bankRecord& bankRecord::setSum(const ulong sum) {
    if (sum>0) {
        this->sum = sum;
        return (*this);
    } else {
//        throw std::domain_error("Sum can only be positive");
    }

}

bankRecord& bankRecord::setSender(const string &sender) {
    this->sender = sender;
    return (*this);
}

bankRecord& bankRecord::setReceiver(const string &receiver) {
    this->receiver = receiver;
    return (*this);
}

bankRecord& bankRecord::setDate(const QDate &date) {
    this->date = date;
    return (*this);
}

/****************** get methods ******************/

int bankRecord::getID() const {
    return this->ID;
}

float bankRecord::getSum() const {
    return this->sum;
}

string bankRecord::getSender() const {
    return this->sender;
}

string bankRecord::getReceiver() const {
    return this->receiver;
}

QDate bankRecord::getDate() const {
    return this->date;
}

string bankRecord::toString() const {
    ostringstream strStream;
    strStream << "Record ID:  " << ID << endl;
    strStream << "  Summ:     " << sum << endl;
    strStream << "  Sender:   " << sender << endl;
    strStream << "  Receiver: " << receiver << endl;
    strStream << "  DATE:     " << date.day() << "." << date.month() << "." << date.year() << endl;
//    if (toFile) {
//        ofstream outfile("../lab1_ui/bankRecord" + to_string(ID) + ".txt");
//        outfile << strStream.str();
//        outfile.close();
//    }
    return strStream.str();
}

QString bankRecord::getCurrency() const {
    return "";
}

QString bankRecord::getCountry() const {
    return "";
}

string bankRecord::toFileString() const {
    ostringstream strStream;
    strStream << 0 << endl;

    strStream << sum << endl;
    strStream << sender << endl;
    strStream << receiver << endl;
    strStream << date.day() << "." << date.month() << "." << date.year() << endl;
    return strStream.str();
}

bankRecord& bankRecord::operator+=(const ulong rhs) {
    sum+=rhs;
    return *this;
}
bankRecord& bankRecord::operator+=(const bankRecord& rhs) {
    sum+=rhs.getSum();
    return *this;
}
bankRecord& bankRecord::operator-=(const ulong rhs) {
  sum-=rhs;
  return *this;
}
bankRecord& bankRecord::operator-=(const bankRecord& rhs) {
  sum-=rhs.getSum();
  return *this;
}
bankRecord bankRecord::operator+(const bankRecord& rhs) const {
    bankRecord tmp(*this);
    tmp.sum += rhs.getSum();
    return (tmp);
}
bankRecord bankRecord::operator-(const bankRecord& rhs) const {
    bankRecord tmp(*this);
    tmp.sum -= rhs.getSum();
    return (tmp);
}

bankRecord& bankRecord::operator++()
{
    ++(this->sum);
    return *this;
}
bankRecord bankRecord::operator++(int)
{
    bankRecord tmp(*this);
    operator++();
    return tmp;
}
bankRecord& bankRecord::operator--()
{
    --(this->sum);
    return *this;
}
bankRecord bankRecord::operator--(int)
{
    bankRecord tmp(*this);
    operator--();
    return tmp;
}


//Логические операторы
bool bankRecord::operator&&(const bankRecord& rhs) {
    return (this->getCurrency()==rhs.getCurrency());
}

bool bankRecord::operator||(const bankRecord& rhs) {
    return (this->getCurrency()!=""||rhs.getCurrency()!="");
}
//Присваивания
bankRecord& bankRecord::operator=(bankRecord rhs)
{
    bankRecord temp(rhs);
    swap(*this, temp);
    return *this;
}
//Операторы приведения типа
bankRecord::operator int() {
    return this->getSum();
}
