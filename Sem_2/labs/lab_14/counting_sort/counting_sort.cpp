#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

void countingSort(int * arr, int size) {
    if (size <= 1) return;

    int maxVal = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > maxVal) maxVal = arr[i];
    }

    int * cnt = new int[maxVal + 1]{0};
    int * output = new int[size];

    for (int i = 0; i < size; i++) cnt[arr[i]]++;
    for (int i = 1; i <= maxVal; i++) cnt[i] += cnt[i - 1];
    for (int i = size - 1; i >= 0; i--) {
        output[cnt[arr[i]] - 1] = arr[i];
        cnt[arr[i]]--;
    }
    for (int i = 0; i < size; i++) arr[i] = output[i];

    delete[] cnt;
    delete[] output;
}

int main() {
    srand(time(0));
    int size = 10;
    int * arr = new int[size];

    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 11;
        cout << arr[i] << " ";
    }
    cout << endl;

    countingSort(arr, size);

    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    delete[] arr;
    return 0;
}