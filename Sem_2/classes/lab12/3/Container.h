#pragma once
#include <map>
#include <algorithm>
#include <numeric>
#include <iostream>
using namespace std;

template<class T>
class Container {
    map<int, T> v;
    int len;
public:
    Container() : len(0) {}
    Container(int n) {
        for (int i = 0; i < n; ++i) {
            T x; cin >> x;
            v[i] = x;
        }
        len = n;
    }
    ~Container() {}
    void Print() {
        for (auto& p : v) cout << p.first << ":" << p.second << " ";
        cout << endl;
    }
    T Srednee() {
        T sum(0,0);
        for (auto& p : v) sum = sum + p.second;
        return sum / len;
    }
    int Max() {
        auto it = max_element(v.begin(), v.end(),
            [](const pair<int,T>& a, const pair<int,T>& b) {
                return a.second < b.second;
            });
        return it->first;
    }
    int Min() {
        auto it = min_element(v.begin(), v.end(),
            [](const pair<int,T>& a, const pair<int,T>& b) {
                return a.second < b.second;
            });
        return it->first;
    }
    void AddMaxToEnd() {
        int key = Max();
        T val = v[key];
        int new_key = v.rbegin()->first + 1;
        v[new_key] = val;
        len++;
    }
    void DeleteByKey(T key) {
        for (auto it = v.begin(); it != v.end(); ) {
            if (it->second == key) it = v.erase(it);
            else ++it;
        }
        len = v.size();
    }
    void AddAvgToEach() {
        T avg = Srednee();
        for (auto& p : v) p.second = p.second + avg;
    }
};