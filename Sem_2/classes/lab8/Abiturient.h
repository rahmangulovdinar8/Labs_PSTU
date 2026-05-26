#pragma once
#include "Person.h"
#include <string>
using namespace std;

class Abiturient : public Person {
private:
    int score;
    string specialty;

public:
    Abiturient();
    Abiturient(string, int, int, string);
    Abiturient(const Abiturient&);
    virtual ~Abiturient();

    int getScore() const;
    string getSpecialty() const;
    void setScore(int);
    void setSpecialty(string);

    Abiturient& operator=(const Abiturient&);

    virtual void Show();
    virtual void Input();
    virtual void HandleEvent(const TEvent& e);
};
