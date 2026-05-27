#include <iostream>
#include <map>
#include <algorithm>
#include <numeric>
using namespace std;

map<int,int> make_map(int n) {
    map<int,int> m;
    for (int i = 0; i < n; ++i) {
        int val; cin >> val;
        m[i] = val;
    }
    return m;
}

void print_map(map<int,int> m) {
    for (auto& p : m) cout << p.first << ":" << p.second << " ";
    cout << endl;
}

int srednee(map<int,int> m) {
    int sum = 0;
    for (auto& p : m) sum += p.second;
    return sum / m.size();
}

int Max(map<int,int> m) {
    auto it = max_element(m.begin(), m.end(),
        [](const pair<int,int>& a, const pair<int,int>& b) {
            return a.second < b.second;
        });
    return it->first;
}

int Min(map<int,int> m) {
    auto it = min_element(m.begin(), m.end(),
        [](const pair<int,int>& a, const pair<int,int>& b) {
            return a.second < b.second;
        });
    return it->first;
}

void add_max_to_end(map<int,int>& m) {
    int key = Max(m);
    int val = m[key];
    int new_key = m.rbegin()->first + 1;
    m[new_key] = val;
}

void delete_by_key(map<int,int>& m, int key) {
    m.erase(key);
}

void add_avg_to_each(map<int,int>& m) {
    int avg = srednee(m);
    for (auto& p : m) p.second += avg;
}

int main() {
    int n; cin >> n;
    map<int,int> mp = make_map(n);
    print_map(mp);
    add_max_to_end(mp);
    print_map(mp);
    int key; cin >> key;
    delete_by_key(mp, key);
    print_map(mp);
    add_avg_to_each(mp);
    print_map(mp);
    return 0;
}