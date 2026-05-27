#include "Money.h"
#include <iostream>
#include <deque>
#include <algorithm>
#include <numeric>
using namespace std;

deque<Money> make_deque_money(int n) {
    deque<Money> d;
    for (int i = 0; i < n; ++i) {
        Money m; cin >> m;
        d.push_back(m);
    }
    return d;
}

void print_deque_money(deque<Money> d) {
    for (auto x : d) cout << x << " ";
    cout << endl;
}

void add_max_to_end(deque<Money>& d) {
    Money m = *max_element(d.begin(), d.end());
    d.push_back(m);
}

void delete_by_key(deque<Money>& d, Money key) {
    d.erase(remove(d.begin(), d.end(), key), d.end());
}

void add_avg_to_each(deque<Money>& d) {
    Money avg = accumulate(d.begin(), d.end(), Money(0,0)) / (int)d.size();
    for (auto& x : d) x = x + avg;
}

int main() {
    int n; cin >> n;
    deque<Money> d = make_deque_money(n);
    print_deque_money(d);
    add_max_to_end(d);
    print_deque_money(d);
    Money key; cin >> key;
    delete_by_key(d, key);
    print_deque_money(d);
    add_avg_to_each(d);
    print_deque_money(d);
    return 0;
}