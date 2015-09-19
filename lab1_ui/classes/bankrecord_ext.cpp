#include "bankrecord_ext.h"

void bankRecord_ext::setCountry(const QString &country) {
    this->country = country;
}

void bankRecord_ext::setCurrency(const QString &currency) {
    this->currency = currency;
}

QString bankRecord_ext::getCountry() {
    return country;
}
QString bankRecord_ext::getCurrency() {
    return currency;
}