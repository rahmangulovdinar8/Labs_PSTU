#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class Money {
private:
    long rubles;
    int kopecks;

public:
    Money();
    Money(long, int);
    Money(const Money&);
    ~Money();

    long getRubles() const;
    int getKopecks() const;
    void setRubles(long);
    void setKopecks(int);

    Money& operator=(const Money&);
    bool operator==(const Money&) const;
    bool operator!=(const Money&) const;
    Money operator-(double) const;

    Money& operator--();
    Money operator--(int);

    friend ostream& operator<<(ostream&, const Money&);
    friend istream& operator>>(istream&, Money&);
    friend fstream& operator<<(fstream&, const Money&);
    friend fstream& operator>>(fstream&, Money&);
};
