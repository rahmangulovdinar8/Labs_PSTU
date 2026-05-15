#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int binarySearch(int* arr, int size, int elem) {
    int low = 0;
    int high = size - 1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (elem == arr[mid]) {
            return mid;
        }

        if (elem > arr[mid]) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return -1;
}

void sort(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    srand(time(0));
    int size = 10;
    int* arr = new int[size];

    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }

    sort(arr, size);

    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    int searchElem;
    cout << "Введите число для поиска: ";
    cin >> searchElem;
    int idx = binarySearch(arr, size, searchElem);

    if (idx == -1) {
        cout << "Element not found" << endl;
    }
    else {
        cout << "Element found, index: " << idx << endl;
    }

    delete[] arr;

    return 0;
}