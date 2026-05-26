#pragma once
#include "Object.h"
#include "Event.h"
#include <iostream>
using namespace std;

struct Node {
    Object* data;
    Node* next;
    Node(Object* d) : data(d), next(0) {}
};

class List {
protected:
    Node* head;
    int cur;

public:
    List();
    virtual ~List();

    void Add();
    void Show();
    void Del();
    double AvgAge() const;
    int operator()() const;
    virtual void HandleEvent(const TEvent& e);
};
