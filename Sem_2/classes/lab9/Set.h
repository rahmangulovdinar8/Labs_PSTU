#pragma once
#include <iostream>
using namespace std;

const int MAX_SIZE = 20;

class Set {
private:
    int size;
    int* data;
    
    bool contains(int val) const;
    
public:
    Set();
    Set(int s);
    Set(int s, int* mas);
    Set(const Set& v);
    ~Set();
    
    const Set& operator=(const Set& v);
    int operator[](int i) const;
    Set operator+(int a) const;
    Set operator--();
    int operator()() const { return size; }
    
    friend ostream& operator<<(ostream& out, const Set& v);
    friend istream& operator>>(istream& in, Set& v);
};