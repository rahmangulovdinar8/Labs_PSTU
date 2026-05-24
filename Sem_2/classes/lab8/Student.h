#pragma once
#include "Person.h"

class Student : public Person {
private:
    float rating;
    
public:
    Student();
    Student(string, int, float);
    Student(const Student&);
    virtual ~Student();
    
    float getRating() const;
    void setRating(float);
    
    Student& operator=(const Student&);
    
    virtual void Show();
    virtual void Input();
    virtual void HandleEvent(const TEvent& e);
};