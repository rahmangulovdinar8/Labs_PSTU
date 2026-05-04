#include <iostream>
#include <fstream>
#include <cstring>
#include <clocale>
using namespace std;

struct Patient {
    char fullName[50];
    char address[100];
    int medCardNumber;
    int insuranceNumber;
};

Patient inputPatient() {
    Patient p;
    cin.ignore();
    cout << "ФИО: ";
    cin.getline(p.fullName, 50);
    cout << "Адрес: ";
    cin.getline(p.address, 100);
    cout << "Номер мед. карты: ";
    cin >> p.medCardNumber;
    cout << "Номер страхового полиса: ";
    cin >> p.insuranceNumber;
    return p;
}

void printPatient(Patient p) {
    cout << "ФИО: " << p.fullName << endl;
    cout << "Адрес: " << p.address << endl;
    cout << "Номер мед. карты: " << p.medCardNumber << endl;
    cout << "Номер страхового полиса: " << p.insuranceNumber << endl;
    cout << "-----------------------------" << endl;
}

void createFile(const char* filename, int n) {
    ofstream fout(filename, ios::binary);
    if (!fout) {
        cout << "Ошибка открытия файла!" << endl;
        return;
    }
    for (int i = 0; i < n; i++) {
        cout << "\nВвод пациента " << i + 1 << ":" << endl;
        Patient p = inputPatient();
        fout.write((char*)&p, sizeof(Patient));
    }
    fout.close();
    cout << "Файл создан!" << endl;
}

void printFile(const char* filename) {
    ifstream fin(filename, ios::binary);
    if (!fin) {
        cout << "Ошибка открытия файла!" << endl;
        return;
    }
    Patient p;
    cout << "\nСодержимое файла:" << endl;
    while (fin.read((char*)&p, sizeof(Patient))) {
        printPatient(p);
    }
    fin.close();
}

void deleteByMedCard(const char* filename, int medCard) {
    ifstream fin(filename, ios::binary);
    ofstream fout("temp.dat", ios::binary);
    if (!fin || !fout) {
        cout << "Ошибка открытия файла!" << endl;
        return;
    }
    Patient p;
    bool found = false;
    while (fin.read((char*)&p, sizeof(Patient))) {
        if (p.medCardNumber != medCard) {
            fout.write((char*)&p, sizeof(Patient));
        } else {
            found = true;
        }
    }
    fin.close();
    fout.close();
    remove(filename);
    rename("temp.dat", filename);
    if (found) {
        cout << "Элемент с номером мед. карты " << medCard << " удалён!" << endl;
    } else {
        cout << "Элемент не найден!" << endl;
    }
}

void addTwoPatients(const char* filename) {
    ifstream fin(filename, ios::binary);
    ofstream fout("temp.dat", ios::binary);
    if (!fin || !fout) {
        cout << "Ошибка открытия файла!" << endl;
        return;
    }
    cout << "\nВвод 2 новых пациентов:" << endl;
    Patient newPatients[2];
    for (int i = 0; i < 2; i++) {
        cout << "\nПациент " << i + 1 << ":" << endl;
        newPatients[i] = inputPatient();
    }
    for (int i = 0; i < 2; i++) {
        fout.write((char*)&newPatients[i], sizeof(Patient));
    }
    Patient p;
    while (fin.read((char*)&p, sizeof(Patient))) {
        fout.write((char*)&p, sizeof(Patient));
    }
    fin.close();
    fout.close();
    remove(filename);
    rename("temp.dat", filename);
    cout << "2 элемента добавлены в начало файла!" << endl;
}

int main() {
    setlocale(LC_ALL, "Russian")
    const char* filename = "patients.dat";
    int choice, n, medCard;
    do {
        cout << "\n========== МЕНЮ ==========" << endl;
        cout << "1. Создать файл" << endl;
        cout << "2. Вывести содержимое файла" << endl;
        cout << "3. Удалить элемент по номеру мед. карты" << endl;
        cout << "4. Добавить 2 элемента в начало" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Сколько пациентов ввести? ";
                cin >> n;
                createFile(filename, n);
                break;
            case 2:
                printFile(filename);
                break;
            case 3:
                cout << "Введите номер мед. карты: ";
                cin >> medCard;
                deleteByMedCard(filename, medCard);
                break;
            case 4:
                addTwoPatients(filename);
                break;
        }
    } while (choice != 0);
    return 0;
}