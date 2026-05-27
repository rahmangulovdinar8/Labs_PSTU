#include "Money.h"
#include <iostream>
#include <map>
#include <algorithm>
#include <numeric>
using namespace std;

map<int,Money> make_map(int n) {
    map<int,Money> m;
    for (int i = 0; i < n; ++i) {
        Money val; cin >> val;
        m[i] = val;
    }
    return m;
}

void print_map(map<int,Money> m) {
    for (auto& p : m) cout << p.first << ":" << p.second << " ";
    cout << endl;
}

Money srednee(map<int,Money> m) {
    Money sum(0,0);
    for (auto& p : m) sum = sum + p.second;
    return sum / (int)m.size();
}

int Max(map<int,Money> m) {
    auto it = max_element(m.begin(), m.end(),
        [](const pair<int,Money>& a, const pair<int,Money>& b) {
            return a.second < b.second;
        });
    return it->first;
}

int Min(map<int,Money> m) {
    auto it = min_element(m.begin(), m.end(),
        [](const pair<int,Money>& a, const pair<int,Money>& b) {
            return a.second < b.second;
        });
    return it->first;
}

void add_max_to_end(map<int,Money>& m) {
    int key = Max(m);
    Money val = m[key];
    int new_key = m.rbegin()->first + 1;
    m[new_key] = val;
}

void delete_by_key(map<int,Money>& m, Money key) {
    for (auto it = m.begin(); it != m.end(); ) {
        if (it->second == key) it = m.erase(it);
        else ++it;
    }
}

void add_avg_to_each(map<int,Money>& m) {
    Money avg = srednee(m);
    for (auto& p : m) p.second = p.second + avg;
}

int main() {
    int n; cin >> n;
    map<int,Money> mp = make_map(n);
    print_map(mp);
    add_max_to_end(mp);
    print_map(mp);
    Money key; cin >> key;
    delete_by_key(mp, key);
    print_map(mp);
    add_avg_to_each(mp);
    print_map(mp);
    return 0;
}
