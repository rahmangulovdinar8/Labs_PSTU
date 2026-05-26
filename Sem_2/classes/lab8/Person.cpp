#include "Person.h"
#include <iostream>
using namespace std;

Person::Person() {
    name = "";
    age = 0;
}

Person::Person(string n, int a) {
    name = n;
    age = a;
}

Person::Person(const Person& p) {
    name = p.name;
    age = p.age;
}

Person::~Person() {}

string Person::getName() const { return name; }
int Person::getAge() const { return age; }
void Person::setName(string n) { name = n; }
void Person::setAge(int a) { age = a; }

Person& Person::operator=(const Person& p) {
    if (this != &p) {
        name = p.name;
        age = p.age;
    }
    return *this;
}

void Person::Show() {
    cout << "Человек: " << name << ", возраст: " << age << endl;
}

void Person::Input() {
    cout << "Введите имя: ";
    cin >> name;
    cout << "Введите возраст: ";
    cin >> age;
}

void Person::HandleEvent(const TEvent& e) {
    if (e.what == evMessage) {
        switch (e.command) {
            case cmShow:
                cout << "Имя: " << name << endl;
                break;
        }
    }
}