#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int hoareSplit(int * arr, int low, int high) {
    int pivot = arr[(high + low) / 2];
    int i = low - 1;
    int j = high + 1;

    while (true) {
        do {
            i++;
        } while (arr[i] < pivot);

        do {
            j--;
        } while (arr[j] > pivot);

        if (i >= j) {
            return j;
        }
        swap(arr[i], arr[j]);
    }
}

void hoareSort(int * arr, int low, int high) {
    if (low < high) {
        int pIdx = hoareSplit(arr, low, high);
        hoareSort(arr, low, pIdx);
        hoareSort(arr, pIdx + 1, high);
    }
}

int main() {
    srand(time(0));
    int size = 10;
    int * arr = new int[size];

    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
        cout << arr[i] << " ";
    }
    cout << endl;

    hoareSort(arr, 0, size - 1);

    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    delete[] arr;

    return 0;
}