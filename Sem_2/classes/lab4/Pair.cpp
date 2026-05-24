#include "Pair.h"
#include <iostream>
using namespace std;

Pair::Pair() {
    first = 0;
    second = 0;
}

Pair::Pair(int f, int s) {
    first = f;
    second = s;
}

Pair::Pair(const Pair& p) {
    first = p.first;
    second = p.second;
}

Pair::~Pair() {}

int Pair::getFirst() const { return first; }
int Pair::getSecond() const { return second; }
void Pair::setFirst(int f) { first = f; }
void Pair::setSecond(int s) { second = s; }

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

ostream& operator<<(ostream& out, const Pair& p) {
    out << "(" << p.first << ":" << p.second << ")";
    return out;
}

istream& operator>>(istream& in, Pair& p) {
    cout << "Первое число: ";
    in >> p.first;
    cout << "Второе число: ";
    in >> p.second;
    return in;
}