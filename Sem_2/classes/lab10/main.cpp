#include "Pair.h"
#include "file_work.h"
#include <iostream>
#include <clocale>
#include <string>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    
    Pair key;
    char file_name[30];
    int choice;
    int result;
    int N, K;
    double L;
    
    do {
        cout << "\n========== МЕНЮ ==========" << endl;
        cout << "1. Создать файл" << endl;
        cout << "2. Вывести содержимое файла" << endl;
        cout << "3. Удалить записи равные заданному значению" << endl;
        cout << "4. Уменьшить записи с заданным значением на L" << endl;
        cout << "5. Добавить K записей после записи с номером N" << endl;
        cout << "0. Выход" << endl;
        cout << "Ваш выбор: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Имя файла: ";
                cin >> file_name;
                result = make_file(file_name);
                if (result < 0)
                    cout << "Ошибка создания файла!" << endl;
                else
                    cout << "Файл создан, записей: " << result << endl;
                break;
                
            case 2:
                cout << "Имя файла: ";
                cin >> file_name;
                result = print_file(file_name);
                if (result < 0)
                    cout << "Ошибка открытия файла!" << endl;
                else if (result == 0)
                    cout << "Файл пуст!" << endl;
                else
                    cout << "Всего записей: " << result << endl;
                break;
                
            case 3:
                cout << "Имя файла: ";
                cin >> file_name;
                cout << "Введите пару для удаления:" << endl;
                cin >> key;
                result = del_equal(file_name, key);
                if (result < 0)
                    cout << "Ошибка открытия файла!" << endl;
                else
                    cout << "Осталось записей: " << result << endl;
                break;
                
            case 4:
                cout << "Имя файла: ";
                cin >> file_name;
                cout << "Введите пару для поиска:" << endl;
                cin >> key;
                cout << "Введите число L для вычитания: ";
                cin >> L;
                result = decrease_by_value(file_name, key, L);
                if (result < 0)
                    cout << "Ошибка открытия файла!" << endl;
                else
                    cout << "Обработано записей: " << result << endl;
                break;
                
            case 5:
                cout << "Имя файла: ";
                cin >> file_name;
                cout << "Номер записи, после которой добавлять (N): ";
                cin >> N;
                cout << "Количество добавляемых записей (K): ";
                cin >> K;
                result = add_after(file_name, N, K);
                if (result < 0)
                    cout << "Ошибка открытия файла!" << endl;
                else
                    cout << "Операция завершена" << endl;
                break;
                
            case 0:
                cout << "До свидания!" << endl;
                break;
                
            default:
                cout << "Неверный выбор!" << endl;
        }
    } while (choice != 0);
    
    return 0;
}