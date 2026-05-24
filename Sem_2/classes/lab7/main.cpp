#include "Set.h"
#include "Time.h"
#include <iostream>
#include <clocale>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    
    cout << "=== Set<int> ===" << endl;
    Set<int> intSet1(5, 10);
    Set<int> intSet2(3, 20);
    
    cout << "intSet1: " << intSet1 << endl;
    cout << "intSet2: " << intSet2 << endl;
    
    intSet1[2] = 15;
    cout << "После изменения intSet1[2]=15: " << intSet1 << endl;
    
    Set<int> intSet3 = intSet1 + intSet2;
    cout << "Объединение: " << intSet3 << endl;
    
    cout << "\n=== Set<double> ===" << endl;
    Set<double> doubleSet(4, 1.5);
    cout << "doubleSet: " << doubleSet << endl;
    
    cout << "\n=== Set<Time> ===" << endl;
    Set<Time> timeSet(3);
    cout << "Введите 3 временных интервала (минуты и секунды):" << endl;
    cin >> timeSet;
    cout << "timeSet: " << timeSet << endl;
    
    Time t1(5, 30);
    Set<Time> timeSet2(2, t1);
    cout << "timeSet2: " << timeSet2 << endl;
    
    Set<Time> timeSet3 = timeSet + timeSet2;
    cout << "Объединение: " << timeSet3 << endl;
    
    cout << "\nОбход timeSet с помощью итератора:" << endl;
    for (Iterator<Time> it = timeSet.first(); it != timeSet.last(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    return 0;
}