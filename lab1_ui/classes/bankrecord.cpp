#include "bankrecord.h"
#include <fstream>


using namespace std;

int bankRecord::id = 0;

/****************** set methods ******************/
bankRecord& bankRecord::setSum(ulong sum) {
    if (sum>0) {
        this->sum = sum;
        return (*this);
    } else {
        throw domain_error("Sum can only be positive");
    }

}

bankRecord* bankRecord::setSender(string sender) {
    this->sender = sender;
    return (this);
}

bankRecord* bankRecord::setReceiver(string receiver) {
    this->receiver = receiver;
    return (this);
}

bankRecord& bankRecord::setDate(QDate date) {
    this->date = date;
    return (*this);
}

/****************** get methods ******************/

int bankRecord::getID() {
    return this->ID;
}

float bankRecord::getSum() const {
    return this->sum;
}

string bankRecord::getSender() {
    return this->sender;
}

string bankRecord::getReceiver() {
    return this->receiver;
}

QDate bankRecord::getDate() {
    return this->date;
}

string bankRecord::toString(bool toFile) {
    ostringstream strStream;
    strStream << "Record ID:  " << ID << endl;
    strStream << "  Summ:     " << sum << endl;
    strStream << "  Sender:   " << sender << endl;
    strStream << "  Receiver: " << receiver << endl;
    strStream << "  DATE:     " << date.toString().toStdString() << endl;
    if (toFile) {
        ofstream outfile("bankRecord" + to_string(ID) + ".txt");
        outfile << strStream.str();
        outfile.close();
    }
    return strStream.str();
}

QString bankRecord::getCurrency() const {
    return "";
}

QString bankRecord::getCountry() const {
    return "";
}
