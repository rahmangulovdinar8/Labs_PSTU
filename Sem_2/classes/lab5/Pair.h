#pragma once
#include "Object.h"
#include <iostream>
using namespace std;

class Pair : public Object {
protected:
    int first;
    int second;
    
public:
    Pair();
    Pair(int, int);
    Pair(const Pair&);
    virtual ~Pair();
    
    int getFirst() const;
    int getSecond() const;
    void setFirst(int);
    void setSecond(int);
    
    Pair& operator=(const Pair&);
    bool operator==(const Pair&) const;
    bool operator<(const Pair&) const;
    bool operator>(const Pair&) const;
    
    virtual void Show();
    
    friend ostream& operator<<(ostream&, const Pair&);
    friend istream& operator>>(istream&, Pair&);
};
