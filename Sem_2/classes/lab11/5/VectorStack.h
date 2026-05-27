#pragma once
#include <stack>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
using namespace std;

template<class T>
class Vector {
    stack<T> s;
    int len;
    vector<T> toVector() {
        vector<T> v;
        stack<T> tmp = s;
        while (!tmp.empty()) {
            v.push_back(tmp.top());
            tmp.pop();
        }
        reverse(v.begin(), v.end());
        return v;
    }
    void fromVector(const vector<T>& v) {
        while (!s.empty()) s.pop();
        for (auto x : v) s.push(x);
        len = v.size();
    }
public:
    Vector() : len(0) {}
    Vector(int n) {
        for (int i = 0; i < n; ++i) {
            T x; cin >> x;
            s.push(x);
        }
        len = n;
    }
    Vector(const Vector<T>& other) {
        vector<T> v = other.toVector();
        fromVector(v);
    }
    void Print() {
        vector<T> v = toVector();
        for (auto x : v) cout << x << " ";
        cout << endl;
    }
    T Srednee() {
        vector<T> v = toVector();
        T sum = accumulate(v.begin(), v.end(), T());
        return sum / (int)v.size();
    }
    void Add(T el, int pos) {
        vector<T> v = toVector();
        if (pos >= 0 && pos <= v.size()) v.insert(v.begin() + pos, el);
        fromVector(v);
    }
    T Max() {
        vector<T> v = toVector();
        return *max_element(v.begin(), v.end());
    }
    void Del() {
        vector<T> v = toVector();
        T m = *max_element(v.begin(), v.end());
        v.erase(remove(v.begin(), v.end(), m), v.end());
        fromVector(v);
    }
    T Min() {
        vector<T> v = toVector();
        return *min_element(v.begin(), v.end());
    }
    void AddAvgToEach() {
        vector<T> v = toVector();
        T avg = Srednee();
        for (auto& x : v) x = x + avg;
        fromVector(v);
    }
    void DeleteByKey(T key) {
        vector<T> v = toVector();
        v.erase(remove(v.begin(), v.end(), key), v.end());
        fromVector(v);
    }
};