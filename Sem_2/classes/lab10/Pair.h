#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Pair {
private:
    int first;
    double second;
    
public:
    Pair();
    Pair(int, double);
    Pair(const Pair&);
    ~Pair();
    
    int getFirst() const;
    double getSecond() const;
    void setFirst(int);
    void setSecond(double);
    
    Pair& operator=(const Pair&);
    bool operator==(const Pair&) const;
    bool operator!=(const Pair&) const;
    bool operator<(const Pair&) const;
    bool operator>(const Pair&) const;
    Pair operator-(const Pair&) const;
    Pair operator+(double k) const;
    Pair operator-(double k) const;
    
    friend ostream& operator<<(ostream&, const Pair&);
    friend istream& operator>>(istream&, Pair&);
    friend fstream& operator<<(fstream&, const Pair&);
    friend fstream& operator>>(fstream&, Pair&);
};