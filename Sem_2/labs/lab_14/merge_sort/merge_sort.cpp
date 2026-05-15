#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

void merge(int* arr, int left, int mid, int right) {
    int left_len = mid - left + 1;
    int right_len = right - mid;

    int* left_arr = new int[left_len];
    int* right_arr = new int[right_len];

    for (int i = 0; i < left_len; i++) {
        left_arr[i] = arr[left + i];
    }
    for (int i = 0; i < right_len; i++) {
        right_arr[i] = arr[mid + i + 1];
    }

    int left_index = 0;
    int right_index = 0;
    int merge_index = left;

    while (left_index < left_len && right_index < right_len) {
        if (left_arr[left_index] <= right_arr[right_index]) {
            arr[merge_index] = left_arr[left_index];
            left_index++;
        }
        else {
            arr[merge_index] = right_arr[right_index];
            right_index++;
        }
        merge_index++;
    }

    while(left_index < left_len) {
        arr[merge_index] = left_arr[left_index];
        left_index++;
        merge_index++;
    }

    while(right_index < right_len) {
        arr[merge_index] = right_arr[right_index];
        right_index++;
        merge_index++;
    }

    delete[] left_arr;
    delete[] right_arr;
}

void merge_sort(int* arr, int start, int end) {
    if (start >= end) return;

    int mid = (start + end) / 2;

    merge_sort(arr, start, mid);
    merge_sort(arr, mid + 1, end);
    merge(arr, start, mid, end);
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

    merge_sort(arr, 0, size - 1);

    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    delete[] arr;

    return 0;
}