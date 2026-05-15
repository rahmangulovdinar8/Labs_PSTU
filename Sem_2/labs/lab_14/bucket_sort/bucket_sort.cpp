#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

void bucketSort(int* arr, int size) {
    if (size <= 1) return;

    const int BUCKET_NUM = 10;
    const int BUCKET_SIZE = 100;
    int buckets[BUCKET_NUM][BUCKET_SIZE];
    int bucketSizes[BUCKET_NUM] = {0};

    int maxVal = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }

    for (int i = 0; i < size; i++) {
        int bucketIdx = (BUCKET_NUM * arr[i]) / (maxVal + 1);
        
        if (bucketSizes[bucketIdx] < BUCKET_SIZE) {
            buckets[bucketIdx][bucketSizes[bucketIdx]] = arr[i];
            bucketSizes[bucketIdx]++;
        }
    }

    for (int i = 0; i < BUCKET_NUM; i++) {
        for (int j = 1; j < bucketSizes[i]; j++) {
            int tmp = buckets[i][j];
            int k = j - 1;

            while (k >= 0 && buckets[i][k] > tmp) {
                buckets[i][k + 1] = buckets[i][k];
                k--;
            }
            buckets[i][k + 1] = tmp;
        }
    }

    int idx = 0;
    for (int i = 0; i < BUCKET_NUM; i++) {
        for (int j = 0; j < bucketSizes[i]; j++) {
            arr[idx++] = buckets[i][j];
        }
    }
}

int main() {
    srand(time(0));
    int size = 10;
    int* arr = new int[size];

    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 101;
        cout << arr[i] << " ";
    }
    cout << endl;

    bucketSort(arr, size);

    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    delete[] arr;

    return 0;
}