#include "Vector.h"
#include "Date.h"
#include <iostream>
#include <clocale>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    
    Vector v(5);
    
    Pair* p1 = new Pair(10, 20);
    Date* d1 = new Date(2024, 6, 15);
    Pair* p2 = new Pair(30, 40);
    Date* d2 = new Date(2025, 12, 31);
    
    v.Add(p1);
    v.Add(d1);
    v.Add(p2);
    v.Add(d2);
    
    cout << "Содержимое вектора:" << endl;
    cout << v;
    
    delete p1;
    delete d1;
    delete p2;
    delete d2;
    
    return 0;
}