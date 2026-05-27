#include "Money.h"

Money::Money() { rubles = 0; kopecks = 0; }
Money::Money(long r, int k) { rubles = r; kopecks = k; }
Money::Money(const Money& m) { rubles = m.rubles; kopecks = m.kopecks; }
Money::~Money() {}

long Money::getRubles()  const { return rubles; }
int  Money::getKopecks() const { return kopecks; }
void Money::setRubles(long r)  { rubles = r; }
void Money::setKopecks(int k)  { kopecks = k; }

Money Money::operator=(const Money& m) {
    if (this == &m) return *this;
    rubles = m.rubles; kopecks = m.kopecks;
    return *this;
}

bool Money::operator==(const Money& m) const {
    return rubles == m.rubles && kopecks == m.kopecks;
}

bool Money::operator!=(const Money& m) const { return !(*this == m); }

bool Money::operator>(const Money& m) const {
    if (rubles > m.rubles) return true;
    if (rubles == m.rubles && kopecks > m.kopecks) return true;
    return false;
}

bool Money::operator<(const Money& m) const {
    if (rubles < m.rubles) return true;
    if (rubles == m.rubles && kopecks < m.kopecks) return true;
    return false;
}

Money Money::operator-(double d) const {
    long total = rubles * 100 + kopecks - (long)(d * 100);
    if (total < 0) total = 0;
    return Money(total / 100, total % 100);
}

Money Money::operator+(const Money& m) const {
    long total = rubles * 100 + kopecks + m.rubles * 100 + m.kopecks;
    return Money(total / 100, total % 100);
}

Money Money::operator/(int n) const {
    if (n == 0) return Money(0, 0);
    long total = rubles * 100 + kopecks;
    return Money((total / n) / 100, (total / n) % 100);
}

ostream& operator<<(ostream& out, const Money& m) {
    out << m.rubles << "р " << m.kopecks << "к";
    return out;
}

istream& operator>>(istream& in, Money& m) {
    cout << "Рублей: "; in >> m.rubles;
    cout << "Копеек: "; in >> m.kopecks;
    return in;
}

fstream& operator<<(fstream& out, const Money& m) {
    out << m.rubles << "\n" << m.kopecks << "\n";
    return out;
}

fstream& operator>>(fstream& in, Money& m) {
    in >> m.rubles >> m.kopecks;
    return in;
}
