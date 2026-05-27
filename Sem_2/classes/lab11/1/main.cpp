#include <iostream>
#include <deque>
#include <algorithm>
#include <numeric>
using namespace std;

deque<int> make_deque(int n) {
    deque<int> d;
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        d.push_back(x);
    }
    return d;
}

void print_deque(deque<int> d) {
    for (auto x : d) cout << x << " ";
    cout << endl;
}

int find_max(deque<int> d) {
    return max_element(d.begin(), d.end()) - d.begin();
}

void add_max_to_end(deque<int>& d) {
    int m = *max_element(d.begin(), d.end());
    d.push_back(m);
}

void delete_by_key(deque<int>& d, int key) {
    d.erase(remove(d.begin(), d.end(), key), d.end());
}

void add_avg_to_each(deque<int>& d) {
    int avg = accumulate(d.begin(), d.end(), 0) / d.size();
    for (auto& x : d) x += avg;
}

int main() {
    int n; cin >> n;
    deque<int> d = make_deque(n);
    print_deque(d);
    add_max_to_end(d);
    print_deque(d);
    int key; cin >> key;
    delete_by_key(d, key);
    print_deque(d);
    add_avg_to_each(d);
    print_deque(d);
    return 0;
}