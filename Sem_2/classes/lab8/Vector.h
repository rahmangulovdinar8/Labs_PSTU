#pragma once
#include "Object.h"
#include "Event.h"
#include <iostream>
using namespace std;

class Vector {
protected:
    Object** beg;
    int size;
    int cur;
    
public:
    Vector();
    Vector(int);
    virtual ~Vector();
    
    void Add();
    void Show();
    void Del();
    int operator()() const;
    virtual void HandleEvent(const TEvent& e);
};