#include "Vector.h"
#include "Person.h"
#include "Student.h"
#include <iostream>
using namespace std;

Vector::Vector() {
    beg = 0;
    size = 0;
    cur = 0;
}

Vector::Vector(int n) {
    beg = new Object*[n];
    cur = 0;
    size = n;
}

Vector::~Vector() {
    if (beg != 0) delete[] beg;
    beg = 0;
}

void Vector::Add() {
    Object* p;
    cout << "Выберите тип объекта:" << endl;
    cout << "1. Person (Человек)" << endl;
    cout << "2. Student (Студент)" << endl;
    int y;
    cin >> y;
    
    if (y == 1) {
        Person* a = new Person;
        a->Input();
        p = a;
        if (cur < size) {
            beg[cur] = p;
            cur++;
        }
    } else if (y == 2) {
        Student* b = new Student;
        b->Input();
        p = b;
        if (cur < size) {
            beg[cur] = p;
            cur++;
        }
    }
}

void Vector::Show() {
    if (cur == 0) {
        cout << "Группа пуста!" << endl;
        return;
    }
    cout << "\n=== Содержимое группы ===" << endl;
    Object** p = beg;
    for (int i = 0; i < cur; i++) {
        cout << i + 1 << ". ";
        (*p)->Show();
        p++;
    }
}

void Vector::Del() {
    if (cur == 0) return;
    cur--;
}

int Vector::operator()() const {
    return cur;
}

void Vector::HandleEvent(const TEvent& e) {
    if (e.what == evMessage) {
        Object** p = beg;
        for (int i = 0; i < cur; i++) {
            (*p)->HandleEvent(e);
            p++;
        }
    }
}