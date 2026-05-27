#pragma once
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
using namespace std;

template<class T>
class Vector {
    vector<T> v;
    int len;
public:
    Vector() : len(0) {}
    Vector(int n) {
        v.resize(n);
        for (int i = 0; i < n; ++i) cin >> v[i];
        len = n;
    }
    ~Vector() {}
    void Print() {
        for (auto x : v) cout << x << " ";
        cout << endl;
    }
    T Srednee() {
        T sum = accumulate(v.begin(), v.end(), T());
        return sum / (int)v.size();
    }
    void Add(T el, int pos) {
        if (pos >= 0 && pos <= v.size()) v.insert(v.begin() + pos, el);
        len++;
    }
    int Max() {
        return max_element(v.begin(), v.end()) - v.begin();
    }
    void Del(int pos) {
        if (pos >= 0 && pos < v.size()) v.erase(v.begin() + pos);
        len--;
    }
    void AddAvgToEach() {
        T avg = Srednee();
        for (auto& x : v) x = x + avg;
    }
    void DeleteByKey(T key) {
        v.erase(remove(v.begin(), v.end(), key), v.end());
        len = v.size();
    }
};