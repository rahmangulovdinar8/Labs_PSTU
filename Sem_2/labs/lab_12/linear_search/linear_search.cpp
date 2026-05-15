#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int linearSearch(int* arr, int size, int elem) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == elem) {
            return i;
        }
    }
    return -1;
}

int main() {
    srand(time(0));
    int size = 10;
    int* arr = new int[size];

    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
        cout << arr[i] << " ";
    }
    cout << endl;

    int searchElem;
    cout << "Введите число для поиска: ";
    cin >> searchElem;

    int idx = linearSearch(arr, size, searchElem);

    if (idx == -1) {
        cout << "Element not found" << endl;
    } else {
        cout << "Element found, index: " << idx << endl;
    }
    
    delete[] arr;
    return 0;
}