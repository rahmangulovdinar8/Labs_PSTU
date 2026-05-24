#include "Date.h"
#include <iostream>
#include <clocale>
using namespace std;

void f1(Pair& p) {
    p.setFirst(100);
    p.setSecond(200);
    cout << "В функции f1: " << p << endl;
}

Pair f2() {
    Date dt(2025, 12, 31);
    return dt;
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    Date d1;
    cout << "Введите дату:\n";
    cin >> d1;
    cout << "Дата: " << d1 << endl;
    
    Date d2(2024, 6, 15);
    cout << "\nВторая дата: " << d2 << endl;
    
    if (d1 == d2){
        cout << "Даты равны" << endl;
    } else if (d1 < d2){
        cout << d1 << " раньше " << d2 << endl;
    } else{
        cout << d1 << " позже " << d2 << endl;
    }
    Date d3;
    d3 = d1;
    cout << "\nПосле присваивания d3 = d1: " << d3 << endl;
    
    cout << "\nПринцип подстановки" << endl;
    f1(d1);
    
    Date d4 = (Date)f2();
    cout << "Результат f2(): " << d4 << endl;
    
    return 0;
}