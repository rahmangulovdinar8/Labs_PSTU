#include "Vector.h"
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
    int imax = vec.Max();
    vec.Del(imax);
    vec.Print();
    vec.AddAvgToEach();
    vec.Print();
    Money key; cin >> key;
    vec.DeleteByKey(key);
    vec.Print();
    return 0;
}