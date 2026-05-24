#include "Pair.h"
#include <iostream>
#include <fstream>
using namespace std;

Pair::Pair() {
    first = 0;
    second = 0.0;
}

Pair::Pair(int f, double s) {
    first = f;
    second = s;
}

Pair::Pair(const Pair& p) {
    first = p.first;
    second = p.second;
}

Pair::~Pair() {}

int Pair::getFirst() const { return first; }
double Pair::getSecond() const { return second; }
void Pair::setFirst(int f) { first = f; }
void Pair::setSecond(double s) { second = s; }

Pair& Pair::operator=(const Pair& p) {
    if (this != &p) {
        first = p.first;
        second = p.second;
    }
    return *this;
}

bool Pair::operator==(const Pair& p) const {
    return (first == p.first && second == p.second);
}

bool Pair::operator!=(const Pair& p) const {
    return !(*this == p);
}

bool Pair::operator<(const Pair& p) const {
    if (first < p.first) return true;
    if (first == p.first && second < p.second) return true;
    return false;
}

bool Pair::operator>(const Pair& p) const {
    if (first > p.first) return true;
    if (first == p.first && second > p.second) return true;
    return false;
}

Pair Pair::operator-(const Pair& p) const {
    return Pair(first - p.first, second - p.second);
}

Pair Pair::operator+(double k) const {
    return Pair(first + (int)k, second);
}

Pair Pair::operator-(double k) const {
    return Pair(first - (int)k, second);
}

ostream& operator<<(ostream& out, const Pair& p) {
    out << p.first << ":" << p.second;
    return out;
}

istream& operator>>(istream& in, Pair& p) {
    cout << "Первое число (int): ";
    in >> p.first;
    cout << "Второе число (double): ";
    in >> p.second;
    return in;
}

fstream& operator<<(fstream& fout, const Pair& p) {
    fout << p.first << "\n" << p.second << "\n";
    return fout;
}

fstream& operator>>(fstream& fin, Pair& p) {
    fin >> p.first;
    fin >> p.second;
    return fin;
}