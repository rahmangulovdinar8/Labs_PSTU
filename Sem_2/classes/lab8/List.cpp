#include "List.h"
#include "Person.h"
#include "Abiturient.h"
#include <iostream>
using namespace std;

List::List() {
    head = 0;
    cur = 0;
}

List::~List() {
    Node* p = head;
    while (p != 0) {
        Node* next = p->next;
        delete p->data;
        delete p;
        p = next;
    }
}

void List::Add() {
    cout << "Выберите тип объекта:" << endl;
    cout << "1. Person (Человек)" << endl;
    cout << "2. Abiturient (Абитуриент)" << endl;
    int y;
    cin >> y;

    Object* obj = 0;
    if (y == 1) {
        Person* p = new Person;
        p->Input();
        obj = p;
    } else if (y == 2) {
        Abiturient* ab = new Abiturient;
        ab->Input();
        obj = ab;
    }

    if (obj != 0) {
        Node* newNode = new Node(obj);
        if (head == 0) {
            head = newNode;
        } else {
            Node* p = head;
            while (p->next != 0) p = p->next;
            p->next = newNode;
        }
        cur++;
    }
}

void List::Show() {
    if (cur == 0) {
        cout << "Список пуст!" << endl;
        return;
    }
    cout << "\n=== Содержимое списка ===" << endl;
    Node* p = head;
    int i = 1;
    while (p != 0) {
        cout << i++ << ". ";
        p->data->Show();
        p = p->next;
    }
}

void List::Del() {
    if (head == 0) return;
    if (head->next == 0) {
        delete head->data;
        delete head;
        head = 0;
    } else {
        Node* p = head;
        while (p->next->next != 0) p = p->next;
        delete p->next->data;
        delete p->next;
        p->next = 0;
    }
    cur--;
}

double List::AvgAge() const {
    if (cur == 0) return 0;
    int sum = 0;
    Node* p = head;
    while (p != 0) {
        Person* person = dynamic_cast<Person*>(p->data);
        if (person != 0) sum += person->getAge();
        p = p->next;
    }
    return (double)sum / cur;
}

int List::operator()() const { return cur; }

void List::HandleEvent(const TEvent& e) {
    if (e.what == evMessage) {
        Node* p = head;
        while (p != 0) {
            p->data->HandleEvent(e);
            p = p->next;
        }
    }
}
