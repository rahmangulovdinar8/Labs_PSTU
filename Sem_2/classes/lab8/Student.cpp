#include "Student.h"
#include <iostream>
using namespace std;

Student::Student() : Person() {
    rating = 0;
}

Student::Student(string n, int a, float r) : Person(n, a) {
    rating = r;
}

Student::Student(const Student& s) : Person(s) {
    rating = s.rating;
}

Student::~Student() {}

float Student::getRating() const { return rating; }
void Student::setRating(float r) { rating = r; }

Student& Student::operator=(const Student& s) {
    if (this != &s) {
        Person::operator=(s);
        rating = s.rating;
    }
    return *this;
}

void Student::Show() {
    cout << "Студент: " << name << ", возраст: " << age 
         << ", рейтинг: " << rating << endl;
}

void Student::Input() {
    Person::Input();
    cout << "Введите рейтинг: ";
    cin >> rating;
}

void Student::HandleEvent(const TEvent& e) {
    if (e.what == evMessage) {
        switch (e.command) {
            case cmShow:
                cout << "Студент: " << name << ", рейтинг: " << rating << endl;
                break;
        }
    }
}