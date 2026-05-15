#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int interpolationSearch(int* arr, int size, int searchElem) {
    int low = 0;
    int high = size - 1;

    while (arr[low] <= searchElem && searchElem <= arr[high] && low <= high) {
        if ((low == high) || (arr[low] == arr[high])) {
            if (arr[low] == searchElem) {
                return low;
            } else {
                return -1;
            }
        }
        
        int pos = low + ((searchElem - arr[low]) * (high - low)) / (arr[high] - arr[low]);

        if (arr[pos] == searchElem) {
            return pos;
        } else if (searchElem > arr[pos]) {
            low = pos + 1;
        } else {
            high = pos - 1;
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

    int idx = interpolationSearch(arr, size, searchElem); 

    if (idx == -1) {
        cout << "Elem not found" << endl;
    } else {
        cout << "Elem found, index: " << idx << endl;
    }

    delete[] arr;
    return 0;
}