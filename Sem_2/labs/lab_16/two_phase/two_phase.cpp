#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

void bubbleSort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int phaseOne(const char* inputFile, const char* temp1, const char* temp2, int memorySize) {
    ifstream in(inputFile);
    ofstream out1(temp1);
    ofstream out2(temp2);
    
    int* buffer = new int[memorySize];
    int bufferSize = 0;
    int value;
    int seriesCount = 0;
    bool writeToFirst = true;
    
    while (in >> value) {
        buffer[bufferSize++] = value;
        
        if (bufferSize >= memorySize) {
            bubbleSort(buffer, bufferSize);
            
            ofstream& currentOut = writeToFirst ? out1 : out2;
            for (int i = 0; i < bufferSize; i++) {
                currentOut << buffer[i] << ' ';
            }
            currentOut << '#' << '\n';
            seriesCount++;
            
            bufferSize = 0;
            writeToFirst = !writeToFirst;
        }
    }
    
    if (bufferSize > 0) {
        bubbleSort(buffer, bufferSize);
        ofstream& currentOut = writeToFirst ? out1 : out2;
        for (int i = 0; i < bufferSize; i++) {
            currentOut << buffer[i] << ' ';
        }
        currentOut << '#' << '\n';
        seriesCount++;
    }
    
    delete[] buffer;
    return seriesCount;
}

int readSeries(ifstream& in, int* arr, int maxSize) {
    int count = 0;
    int val;
    
    while (count < maxSize && in >> val && val != '#') {
        arr[count++] = val;
    }
    return count;
}

void mergeSeries(int* arrA, int sizeA, int* arrB, int sizeB, int* result, int& resultSize) {
    int i = 0, j = 0;
    resultSize = 0;
    
    while (i < sizeA && j < sizeB) {
        if (arrA[i] <= arrB[j]) {
            result[resultSize++] = arrA[i++];
        } else {
            result[resultSize++] = arrB[j++];
        }
    }
    
    while (i < sizeA) result[resultSize++] = arrA[i++];
    while (j < sizeB) result[resultSize++] = arrB[j++];
}

int phaseTwo(const char* in1, const char* in2, const char* out1, const char* out2, int memorySize) {
    ifstream f1(in1);
    ifstream f2(in2);
    ofstream fOut1(out1);
    ofstream fOut2(out2);
    
    int* buffer1 = new int[memorySize];
    int* buffer2 = new int[memorySize];
    int* merged = new int[memorySize * 2];
    
    int newSeriesCount = 0;
    bool writeToFirst = true;
    
    while (true) {
        int size1 = readSeries(f1, buffer1, memorySize);
        int size2 = readSeries(f2, buffer2, memorySize);
        
        if (size1 == 0 && size2 == 0) break;
        
        ofstream& currentOut = writeToFirst ? fOut1 : fOut2;
        
        if (size1 > 0 && size2 > 0) {
            int mergedSize;
            mergeSeries(buffer1, size1, buffer2, size2, merged, mergedSize);
            for (int i = 0; i < mergedSize; i++) {
                currentOut << merged[i] << ' ';
            }
        } else if (size1 > 0) {
            for (int i = 0; i < size1; i++) {
                currentOut << buffer1[i] << ' ';
            }
        } else if (size2 > 0) {
            for (int i = 0; i < size2; i++) {
                currentOut << buffer2[i] << ' ';
            }
        }
        
        currentOut << '#' << '\n';
        newSeriesCount++;
        writeToFirst = !writeToFirst;
    }
    
    delete[] buffer1;
    delete[] buffer2;
    delete[] merged;
    
    return newSeriesCount;
}

void twoPhaseSort(const char* input, const char* output, int memorySize) {
    const char* TEMP1 = "temp1.txt";
    const char* TEMP2 = "temp2.txt";
    const char* TEMP3 = "temp3.txt";
    const char* TEMP4 = "temp4.txt";
    
    int series = phaseOne(input, TEMP1, TEMP2, memorySize);
    
    while (series > 1) {
        series = phaseTwo(TEMP1, TEMP2, TEMP3, TEMP4, memorySize);
        remove(TEMP3);
        rename(TEMP1, TEMP3);
        remove(TEMP4);
        rename(TEMP2, TEMP4);
    }
    
    remove(output);
    rename(TEMP1, output);
}

int main() {
    srand(time(0));
    
    int size;
    cout << "Enter size: ";
    cin >> size;
    
    const char* initFile = "init.txt";
    const char* resultFile = "result.txt";
    
    ofstream data(initFile);
    cout << "Before sorting:" << endl;
    for (int i = 0; i < size; i++) {
        int cur = rand() % 100;
        cout << cur << " ";
        data << cur << "\n";
    }
    data.close();
    cout << endl << endl;
    
    twoPhaseSort(initFile, resultFile, 10);
    
    ifstream res(resultFile);
    cout << "After sorting:" << endl;
    int temp;
    while (res >> temp && temp != '#') {
        cout << temp << " ";
    }
    res.close();
    
    return 0;
}