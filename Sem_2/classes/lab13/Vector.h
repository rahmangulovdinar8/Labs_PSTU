#pragma once
#include <vector>
#include <iostream>
using namespace std;

template<class T>
class Vector {
    vector<T> v;
    int len;
public:
    Vector() { len = 0; }
    Vector(int n) {
        T a;
        for (int i = 0; i < n; i++) { cin >> a; v.push_back(a); }
        len = v.size();
    }
    ~Vector() {}

    void Print() {
        for (int i = 0; i < (int)v.size(); i++) cout << v[i] << "  ";
        cout << endl;
    }

    T Srednee() {
        T s = v[0];
        for (int i = 1; i < (int)v.size(); i++) s = s + v[i];
        return s / (int)v.size();
    }

    void Add(T el, int pos) {
        v.insert(v.begin() + pos, el);
        len = v.size();
    }

    int Max() {
        int n = 0;
        T m = v[0];
        for (int i = 1; i < (int)v.size(); i++)
            if (v[i] > m) { m = v[i]; n = i; }
        return n;
    }

    void Del(int pos) {
        v.erase(v.begin() + pos);
        len = v.size();
    }

    void AddMaxToEnd() {
        T m = v[Max()];
        v.push_back(m);
        len = v.size();
    }

    void DeleteByKey(T key) {
        for (int i = 0; i < (int)v.size(); ) {
            if (v[i] == key) { v.erase(v.begin() + i); }
            else i++;
        }
        len = v.size();
    }

    void AddAvgToEach() {
        T avg = Srednee();
        for (int i = 0; i < (int)v.size(); i++) v[i] = v[i] + avg;
    }
};
