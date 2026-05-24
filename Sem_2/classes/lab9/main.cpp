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
        cout << "Множество создано: " << bigSet << endl;
    } catch (MaxSizeError& e) {
        cout << "Исключение перехвачено: ";
        e.what();
    }
    
    try {
        cout << "\nТест 2: Создание множества из 5 элементов" << endl;
        Set mySet(5);
        cout << "Введите 5 элементов множества:" << endl;
        cin >> mySet;
        cout << "Множество: " << mySet << endl;
        
        cout << "\nТест 3: Доступ по индексу" << endl;
        cout << "mySet[2] = " << mySet[2] << endl;
        
        cout << "\nТест 4: Попытка доступа по отрицательному индексу" << endl;
        cout << "mySet[-1] = " << mySet[-1] << endl;
    } catch (IndexError1& e) {
        cout << "Исключение перехвачено: ";
        e.what();
    } catch (IndexError2& e) {
        cout << "Исключение перехвачено: ";
        e.what();
    }
    
    try {
        cout << "\nТест 5: Добавление элемента в множество" << endl;
        Set mySet(3);
        cout << "Введите 3 элемента множества:" << endl;
        cin >> mySet;
        cout << "Множество: " << mySet << endl;
        
        cout << "Добавляем элемент 100..." << endl;
        Set newSet = mySet + 100;
        cout << "Новое множество: " << newSet << endl;
    } catch (MaxSizeError& e) {
        cout << "Исключение перехвачено: ";
        e.what();
    }
    
    try {
        cout << "\nТест 6: Удаление элемента из пустого множества" << endl;
        Set emptySet;
        cout << "Пустое множество: " << emptySet << endl;
        cout << "Пытаемся удалить элемент..." << endl;
        emptySet = --emptySet;
    } catch (EmptySizeError& e) {
        cout << "Исключение перехвачено: ";
        e.what();
    }
    
    try {
        cout << "\nТест 7: Нормальная работа с множеством" << endl;
        Set normalSet(4);
        cout << "Введите 4 элемента множества:" << endl;
        cin >> normalSet;
        cout << "Множество: " << normalSet << endl;
        cout << "Размер множества: " << normalSet() << endl;
        
        cout << "Удаляем последний элемент..." << endl;
        normalSet = --normalSet;
        cout << "Множество после удаления: " << normalSet << endl;
        cout << "Размер множества: " << normalSet() << endl;
    } catch (Error& e) {
        cout << "Исключение перехвачено: ";
        e.what();
    }
    
    cout << "\n=== Программа завершена ===" << endl;
    
    return 0;
}