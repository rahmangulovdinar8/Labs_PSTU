#include "Dialog.h"
#include "Person.h"
#include "Abiturient.h"
#include <iostream>
#include <clocale>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    Dialog D;
    cout << "=== Программа управления списком ===" << endl;
    cout << "Команды:" << endl;
    cout << "  + - добавить элемент" << endl;
    cout << "  - - удалить последний элемент" << endl;
    cout << "  ? - показать список" << endl;
    cout << "  z - средний возраст" << endl;
    cout << "  q - выход" << endl;
    D.Execute();

    return 0;
}
