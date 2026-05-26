#pragma once
#include "Money.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int make_file(const char* f_name) {
    fstream stream(f_name, ios::out | ios::trunc);
    if (!stream) return -1;
    int n;
    Money m;
    cout << "Количество записей: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "\nЗапись " << i + 1 << ":" << endl;
        cin >> m;
        stream << m;
    }
    stream.close();
    return n;
}

int print_file(const char* f_name) {
    fstream stream(f_name, ios::in);
    if (!stream) return -1;
    Money m;
    int i = 0;
    while (stream >> m) {
        cout << i + 1 << ". " << m << endl;
        i++;
    }
    stream.close();
    return i;
}

int del_equal(const char* f_name, const Money& key) {
    fstream temp("temp.txt", ios::out);
    fstream stream(f_name, ios::in);
    if (!stream) return -1;
    Money m;
    int count = 0, removed = 0;
    while (stream >> m) {
        count++;
        if (!(m == key)) temp << m;
        else removed++;
    }
    stream.close();
    temp.close();
    remove(f_name);
    rename("temp.txt", f_name);
    cout << "Удалено записей: " << removed << endl;
    return count - removed;
}

int decrease_equal(const char* f_name, const Money& key) {
    fstream temp("temp.txt", ios::out);
    fstream stream(f_name, ios::in);
    if (!stream) return -1;
    Money m;
    int count = 0, changed = 0;
    while (stream >> m) {
        count++;
        if (m == key) { m = m - 1.50; changed++; }
        temp << m;
    }
    stream.close();
    temp.close();
    remove(f_name);
    rename("temp.txt", f_name);
    cout << "Изменено записей: " << changed << endl;
    return count;
}

int add_after_value(const char* f_name, const Money& key, int K) {
    fstream temp("temp.txt", ios::out);
    fstream stream(f_name, ios::in);
    if (!stream) return -1;
    Money m;
    int added = 0;
    while (stream >> m) {
        temp << m;
        if (m == key) {
            for (int i = 0; i < K; i++) {
                Money newM;
                cout << "\nНовая запись " << i + 1 << ":" << endl;
                cin >> newM;
                temp << newM;
                added++;
            }
        }
    }
    stream.close();
    temp.close();
    remove(f_name);
    rename("temp.txt", f_name);
    cout << "Добавлено записей: " << added << endl;
    return added;
}
