#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class Money {
    long rubles;
    int  kopecks;
public:
    Money();
    Money(long r, int k);
    Money(const Money&);
    ~Money();

    long getRubles()  const;
    int  getKopecks() const;
    void setRubles(long r);
    void setKopecks(int k);

    Money operator=(const Money&);
    bool  operator==(const Money&) const;
    bool  operator!=(const Money&) const;
    bool  operator>(const Money&)  const;
    bool  operator<(const Money&)  const;
    Money operator-(double d) const;
    Money operator+(const Money&)  const;
    Money operator/(int n)         const;

    friend ostream& operator<<(ostream& out, const Money& m);
    friend istream& operator>>(istream& in,  Money& m);
    friend fstream& operator<<(fstream& out, const Money& m);
    friend fstream& operator>>(fstream& in,  Money& m);
};
