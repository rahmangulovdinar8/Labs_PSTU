#include "Money.h"
#include <iostream>
using namespace std;

Money::Money() {
    rubles = 0;
    kopecks = 0;
}

Money::Money(long r, int k) {
    rubles = r;
    kopecks = k;
    if (kopecks >= 100) {
        rubles += kopecks / 100;
        kopecks %= 100;
    }
    if (kopecks < 0) {
        rubles += (kopecks - 99) / 100;
        kopecks = (kopecks % 100 + 100) % 100;
    }
}

Money::Money(const Money& m) {
    rubles = m.rubles;
    kopecks = m.kopecks;
}

Money::~Money() {}

long Money::getRubles() const { return rubles; }
int Money::getKopecks() const { return kopecks; }
void Money::setRubles(long r) { rubles = r; }
void Money::setKopecks(int k) { kopecks = k; }

Money& Money::operator=(const Money& m) {
    if (this != &m) {
        rubles = m.rubles;
        kopecks = m.kopecks;
    }
    return *this;
}

bool Money::operator==(const Money& m) const {
    return (rubles == m.rubles && kopecks == m.kopecks);
}

bool Money::operator!=(const Money& m) const {
    return !(*this == m);
}

Money& Money::operator--() {
    if (kopecks == 0) {
        if (rubles > 0) {
            rubles--;
            kopecks = 99;
        } else {
            rubles = 0;
            kopecks = 0;
        }
    } else {
        kopecks--;
    }
    return *this;
}

Money Money::operator--(int) {
    Money temp = *this;
    --(*this);
    return temp;
}

ostream& operator<<(ostream& out, const Money& m) {
    out << m.rubles << ",";
    if (m.kopecks < 10) out << "0";
    out << m.kopecks;
    return out;
}

istream& operator>>(istream& in, Money& m) {
    cout << "Рубли: ";
    in >> m.rubles;
    cout << "Копейки: ";
    in >> m.kopecks;
    return in;
}
Money Money::operator-(double d) const {
    long totalKop = rubles * 100 + kopecks - (long)(d * 100);
    if (totalKop < 0) totalKop = 0;
    return Money(totalKop / 100, totalKop % 100);
}

fstream& operator<<(fstream& fout, const Money& m) {
    fout << m.rubles << "\n" << m.kopecks << "\n";
    return fout;
}

fstream& operator>>(fstream& fin, Money& m) {
    fin >> m.rubles >> m.kopecks;
    return fin;
}
