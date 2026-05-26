#include "Set.h"
#include <iostream>
#include <clocale>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    Set A(5);
    Set B(5);

    cout << "Введите множество A:" << endl;
    cin >> A;
    cout << "Введите множество B:" << endl;
    cin >> B;

    cout << "A: " << A << endl;
    cout << "B: " << B << endl;

    cout << "A[2] = " << A[2] << endl;
    A[2] = 99;
    cout << "После A[2]=99: " << A << endl;

    cout << "A != B? " << (A != B ? "Да" : "Нет") << endl;

    int val;
    cout << "Введите число для проверки принадлежности A: ";
    cin >> val;
    cout << val << " входит в A? " << (A < val ? "Да" : "Нет") << endl;

    int n;
    cout << "Введите n для сдвига итератора: ";
    cin >> n;
    cout << "Элементы A начиная с позиции " << n << ":" << endl;
    Iterator it = A.first();
    it += n;
    for (; it != A.last(); it += 1)
        cout << *it << " ";
    cout << endl;

    return 0;
}
