#pragma once
#include "Object.h"
#include <iostream>
#include <string>
using namespace std;

class Person : public Object {
protected:
    string name;
    int age;
    
public:
    Person();
    Person(string, int);
    Person(const Person&);
    virtual ~Person();
    
    string getName() const;
    int getAge() const;
    void setName(string);
    void setAge(int);
    
    Person& operator=(const Person&);
    
    virtual void Show();
    virtual void Input();
    virtual void HandleEvent(const TEvent& e);
};