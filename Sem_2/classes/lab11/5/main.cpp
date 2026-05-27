#include "VectorStack.h"
#include "Money.h"
#include <iostream>
using namespace std;

int main() {
    int n; cin >> n;
    Vector<Money> vec(n);
    vec.Print();
    Money avg = vec.Srednee();
    cout << "Avg: " << avg << endl;
    int pos; cin >> pos;
    vec.Add(avg, pos);
    vec.Print();
    Money m = vec.Max();
    cout << "Max: " << m << endl;
    vec.Del();
    vec.Print();
    vec.AddAvgToEach();
    vec.Print();
    Money key; cin >> key;
    vec.DeleteByKey(key);
    vec.Print();
    return 0;
}