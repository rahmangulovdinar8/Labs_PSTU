#include "Money.h"
#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

stack<Money> make_stack(int n) {
    stack<Money> s;
    for (int i = 0; i < n; ++i) {
        Money m; cin >> m;
        s.push(m);
    }
    return s;
}

void print_stack(stack<Money> s) {
    vector<Money> v;
    while (!s.empty()) {
        v.push_back(s.top());
        s.pop();
    }
    for (int i = v.size() - 1; i >= 0; --i) cout << v[i] << " ";
    cout << endl;
}

vector<Money> copy_stack_to_vector(stack<Money> s) {
    vector<Money> v;
    while (!s.empty()) {
        v.push_back(s.top());
        s.pop();
    }
    reverse(v.begin(), v.end());
    return v;
}

stack<Money> copy_vector_to_stack(vector<Money> v) {
    stack<Money> s;
    for (auto x : v) s.push(x);
    return s;
}

void add_max_to_end(stack<Money>& s) {
    vector<Money> v = copy_stack_to_vector(s);
    Money m = *max_element(v.begin(), v.end());
    v.push_back(m);
    s = copy_vector_to_stack(v);
}

void delete_by_key(stack<Money>& s, Money key) {
    vector<Money> v = copy_stack_to_vector(s);
    v.erase(remove(v.begin(), v.end(), key), v.end());
    s = copy_vector_to_stack(v);
}

void add_avg_to_each(stack<Money>& s) {
    vector<Money> v = copy_stack_to_vector(s);
    Money avg = accumulate(v.begin(), v.end(), Money(0,0)) / (int)v.size();
    for (auto& x : v) x = x + avg;
    s = copy_vector_to_stack(v);
}

int main() {
    int n; cin >> n;
    stack<Money> st = make_stack(n);
    print_stack(st);
    add_max_to_end(st);
    print_stack(st);
    Money key; cin >> key;
    delete_by_key(st, key);
    print_stack(st);
    add_avg_to_each(st);
    print_stack(st);
    return 0;
}