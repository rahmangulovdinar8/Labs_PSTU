#include "Dialog.h"
#include "Person.h"
#include "Student.h"
#include <iostream>
#include <clocale>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    
    Dialog D;
    cout << "=== Программа управления группой ===" << endl;
    cout << "Команды:" << endl;
    cout << "  m - создать группу" << endl;
    cout << "  + - добавить элемент" << endl;
    cout << "  - - удалить последний элемент" << endl;
    cout << "  ? - показать группу" << endl;
    cout << "  q - выход" << endl;
    D.Execute();
    
    return 0;
}