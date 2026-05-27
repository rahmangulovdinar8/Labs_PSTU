#include "Container.h"
#include "Money.h"
#include <iostream>
using namespace std;

int main() {
    int n; cin >> n;
    Container<Money> cont(n);
    cont.Print();
    cont.AddMaxToEnd();
    cont.Print();
    Money key; cin >> key;
    cont.DeleteByKey(key);
    cont.Print();
    cont.AddAvgToEach();
    cont.Print();
    return 0;
}