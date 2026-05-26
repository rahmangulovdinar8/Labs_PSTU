#include "Set.h"
#include "Money.h"
#include <iostream>
#include <clocale>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "=== Set<int> ===" << endl;
    Set<int> A(5);
    Set<int> B(5);

    cout << "Введите множество A (5 элементов):" << endl;
    cin >> A;
    cout << "Введите множество B (5 элементов):" << endl;
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
    Iterator<int> it = A.first();
    it += n;
    for (; it != A.last(); it += 1)
        cout << *it << " ";
    cout << endl;

    cout << "\n=== Set<Money> ===" << endl;
    Set<Money> M(3);
    cout << "Введите 3 суммы:" << endl;
    cin >> M;
    cout << "M: " << M << endl;

    Money key;
    cout << "Введите сумму для проверки принадлежности: " << endl;
    cin >> key;
    cout << "Входит в M? " << (M < key ? "Да" : "Нет") << endl;

    return 0;
}
