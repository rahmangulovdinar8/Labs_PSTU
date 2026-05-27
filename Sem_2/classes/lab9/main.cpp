#include "Set.h"
#include "Error.h"
#include <iostream>
#include <clocale>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    try {
        cout << "Тест 1: Создание множества с размером 25 (MAX_SIZE=20)" << endl;
        Set bigSet(25);
    } catch (MaxSizeError& e) {
        cout << "Исключение: "; e.what();
    }

    try {
        cout << "\nТест 2: Создание множества из 5 элементов" << endl;
        Set A(5);
        cin >> A;
        cout << "A: " << A << endl;

        cout << "\nТест 3: Доступ по индексу A[2]" << endl;
        cout << "A[2] = " << A[2] << endl;

        cout << "\nТест 4: Доступ по отрицательному индексу A[-1]" << endl;
        cout << A[-1] << endl;
    } catch (IndexError1& e) {
        cout << "Исключение: "; e.what();
    } catch (IndexError2& e) {
        cout << "Исключение: "; e.what();
    }

    try {
        cout << "\nТест 5: Проверка != " << endl;
        Set A(3), B(3);
        cout << "Введите A:" << endl; cin >> A;
        cout << "Введите B:" << endl; cin >> B;
        cout << "A: " << A << endl;
        cout << "B: " << B << endl;
        cout << "A != B? " << (A != B ? "Да" : "Нет") << endl;
    } catch (Error& e) {
        cout << "Исключение: "; e.what();
    }

    try {
        cout << "\nТест 6: Принадлежность числа множеству (< число)" << endl;
        Set A(4);
        cout << "Введите A:" << endl; cin >> A;
        cout << "A: " << A << endl;
        int val;
        cout << "Введите число: "; cin >> val;
        cout << val << " входит в A? " << (A < val ? "Да" : "Нет") << endl;
    } catch (Error& e) {
        cout << "Исключение: "; e.what();
    }

    try {
        cout << "\nТест 7: Итератор со сдвигом +n" << endl;
        Set A(5);
        cout << "Введите A:" << endl; cin >> A;
        cout << "A: " << A << endl;
        int n;
        cout << "Введите n для сдвига: "; cin >> n;
        Iterator it = A.first();
        it += n;
        cout << "Элементы начиная с позиции " << n << ": ";
        for (; it != A.last(); it += 1)
            cout << *it << " ";
        cout << endl;
    } catch (Error& e) {
        cout << "Исключение: "; e.what();
    }

    return 0;
}
