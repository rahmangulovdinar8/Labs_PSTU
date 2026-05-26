#include "file_work.h"
#include <iostream>
#include <clocale>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    const char* fname = "money.txt";

    cout << "=== Создание файла ===" << endl;
    make_file(fname);

    cout << "\n=== Содержимое файла ===" << endl;
    print_file(fname);

    Money key;
    cout << "\nВведите сумму для удаления равных:" << endl;
    cin >> key;
    del_equal(fname, key);

    cout << "\n=== Файл после удаления ===" << endl;
    print_file(fname);

    cout << "\nВведите сумму для уменьшения на 1р50к:" << endl;
    cin >> key;
    decrease_equal(fname, key);

    cout << "\n=== Файл после уменьшения ===" << endl;
    print_file(fname);

    cout << "\nВведите сумму, после которой добавить записи:" << endl;
    cin >> key;
    int K;
    cout << "Сколько записей добавить: ";
    cin >> K;
    add_after_value(fname, key, K);

    cout << "\n=== Файл после добавления ===" << endl;
    print_file(fname);

    return 0;
}
