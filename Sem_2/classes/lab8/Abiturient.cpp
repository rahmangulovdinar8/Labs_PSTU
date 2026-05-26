#include "Abiturient.h"
#include <iostream>
using namespace std;

Abiturient::Abiturient() : Person() {
    score = 0;
    specialty = "";
}

Abiturient::Abiturient(string n, int a, int s, string sp) : Person(n, a) {
    score = s;
    specialty = sp;
}

Abiturient::Abiturient(const Abiturient& ab) : Person(ab) {
    score = ab.score;
    specialty = ab.specialty;
}

Abiturient::~Abiturient() {}

int Abiturient::getScore() const { return score; }
string Abiturient::getSpecialty() const { return specialty; }
void Abiturient::setScore(int s) { score = s; }
void Abiturient::setSpecialty(string sp) { specialty = sp; }

Abiturient& Abiturient::operator=(const Abiturient& ab) {
    if (this != &ab) {
        Person::operator=(ab);
        score = ab.score;
        specialty = ab.specialty;
    }
    return *this;
}

void Abiturient::Show() {
    cout << "Абитуриент: " << name << ", возраст: " << age
         << ", баллы: " << score << ", специальность: " << specialty << endl;
}

void Abiturient::Input() {
    Person::Input();
    cout << "Введите баллы ЕГЭ: ";
    cin >> score;
    cout << "Введите специальность: ";
    cin >> specialty;
}

void Abiturient::HandleEvent(const TEvent& e) {
    if (e.what == evMessage) {
        switch (e.command) {
            case cmShow:
                cout << "Абитуриент: " << name << ", баллы: " << score << endl;
                break;
        }
    }
}
