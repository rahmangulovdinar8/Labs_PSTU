#include "Set.h"
#include <iostream>
#include <clocale>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    
    Set A(5);
    Set B(4);
    
    cout << "Введите множество A (5 элементов):" << endl;
    cin >> A;
    cout << "\nМножество A: " << A << endl;
    cout << "Размер A: " << A() << endl;
    
    cout << "\nВведите множество B (4 элемента):" << endl;
    cin >> B;
    cout << "\nМножество B: " << B << endl;
    
    cout << "\nA[2] = " << A[2] << endl;
    A[2] = 100;
    cout << "После изменения A[2]=100: " << A << endl;
    
    Set C = A + B;
    cout << "\nОбъединение A и B: " << C << endl;
    
    cout << "\nA == B? " << (A == B ? "Да" : "Нет") << endl;
    
    Set D = A;
    cout << "D = A: " << D << endl;
    cout << "A == D? " << (A == D ? "Да" : "Нет") << endl;
    
    cout << "\nОбход множества A с помощью итератора:" << endl;
    for (Iterator it = A.first(); it != A.last(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    return 0;
}
