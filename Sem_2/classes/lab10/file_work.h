#pragma once
#include "Pair.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

int make_file(const char* f_name) {
    fstream stream(f_name, ios::out | ios::trunc);
    if (!stream) return -1;
    
    int n;
    Pair p;
    cout << "Количество пар: ";
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        cout << "\nПара " << i + 1 << ":" << endl;
        cin >> p;
        stream << p << "\n";
    }
    stream.close();
    return n;
}

int print_file(const char* f_name) {
    fstream stream(f_name, ios::in);
    if (!stream) return -1;
    
    Pair p;
    int i = 0;
    while (stream >> p) {
        cout << i + 1 << ". " << p << endl;
        i++;
    }
    stream.close();
    return i;
}

int del_equal(const char* f_name, const Pair& key) {
    fstream temp("temp.txt", ios::out);
    fstream stream(f_name, ios::in);
    if (!stream) return -1;
    
    Pair p;
    int count = 0;
    int removed = 0;
    
    while (stream >> p) {
        count++;
        if (!(p == key)) {
            temp << p << "\n";
        } else {
            removed++;
        }
    }
    
    stream.close();
    temp.close();
    
    remove(f_name);
    rename("temp.txt", f_name);
    
    cout << "Удалено записей: " << removed << endl;
    return count - removed;
}

int decrease_by_value(const char* f_name, const Pair& key, double L) {
    fstream temp("temp.txt", ios::out);
    fstream stream(f_name, ios::in);
    if (!stream) return -1;
    
    Pair p;
    int count = 0;
    int changed = 0;
    
    while (stream >> p) {
        count++;
        if (p == key) {
            p = p - L;
            changed++;
        }
        temp << p << "\n";
    }
    
    stream.close();
    temp.close();
    
    remove(f_name);
    rename("temp.txt", f_name);
    
    cout << "Изменено записей: " << changed << endl;
    return count;
}

int add_after(const char* f_name, int N, int K) {
    fstream temp("temp.txt", ios::out);
    fstream stream(f_name, ios::in);
    if (!stream) return -1;
    
    Pair p;
    int current = 1;
    int added = 0;
    
    while (current <= N && stream >> p) {
        temp << p << "\n";
        current++;
    }
    
    for (int i = 0; i < K; i++) {
        Pair newPair;
        cout << "\nНовая запись " << i + 1 << " для добавления:" << endl;
        cin >> newPair;
        temp << newPair << "\n";
        added++;
    }
    
    while (stream >> p) {
        temp << p << "\n";
    }
    
    stream.close();
    temp.close();
    
    remove(f_name);
    rename("temp.txt", f_name);
    
    cout << "Добавлено записей: " << added << endl;
    return current + added - 1;
}