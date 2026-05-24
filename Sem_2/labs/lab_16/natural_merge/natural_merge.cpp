#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;


void copyFile(const char* src, const char* dst) {
    ifstream in(src);
    ofstream out(dst);
    int x;
    while (in >> x) {
        out << x << ' ';
    }
}

int distribution(const char* inputFile, const char* file1, const char* file2) {
    ifstream in(inputFile);
    ofstream out1(file1), out2(file2);
    
    if (!in.is_open() || !out1.is_open() || !out2.is_open()) {
        cout << "Ошибка открытия файлов!" << endl;
        return -1;
    }
    
    int current, next;
    int seriesCount = 0;
    bool writeToFirst = true;
    
    if (!(in >> current)) return 0;
    
    seriesCount = 1;
    (writeToFirst ? out1 : out2) << current << ' ';
    
    while (in >> next) {
        if (next < current) {
            seriesCount++;
            writeToFirst = !writeToFirst;
        }
        (writeToFirst ? out1 : out2) << next << ' ';
        current = next;
    }
    
    return seriesCount;
}


int mergeFiles(const char* in1, const char* in2, const char* out1, const char* out2) {
    ifstream f1(in1), f2(in2);
    ofstream fOut1(out1), fOut2(out2);
    
    if (!f1.is_open() || !f2.is_open() || !fOut1.is_open() || !fOut2.is_open()) {
        cout << "Ошибка открытия файлов!" << endl;
        return -1;
    }
    
    int seriesOut = 0;
    bool writeToFirst = true;
    int valueA, valueB;
    bool hasA = (f1 >> valueA);
    bool hasB = (f2 >> valueB);
    
    while (hasA || hasB) {
        seriesOut++;
        ofstream& currentOut = writeToFirst ? fOut1 : fOut2;
        bool endA = false, endB = false;
        
        while (!(endA && endB)) {
            bool takeFromA = false;
            
            if (!endA && hasA && (endB || !hasB || valueA <= valueB)) {
                takeFromA = true;
            } else if (!endB && hasB) {
                takeFromA = false;
            } else {
                break;
            }
            
            if (takeFromA) {
                currentOut << valueA << ' ';
                int nextVal;
                if (f1 >> nextVal) {
                    if (nextVal < valueA) endA = true;
                    valueA = nextVal;
                } else {
                    hasA = false;
                    endA = true;
                }
            } else {
                currentOut << valueB << ' ';
                int nextVal;
                if (f2 >> nextVal) {
                    if (nextVal < valueB) endB = true;
                    valueB = nextVal;
                } else {
                    hasB = false;
                    endB = true;
                }
            }
        }
        writeToFirst = !writeToFirst;
    }
    
    return seriesOut;
}

void externalSort(const char* input, const char* output) {
    const char* F1 = "temp_f1.txt";
    const char* F2 = "temp_f2.txt";
    const char* F3 = "temp_f3.txt";
    const char* F4 = "temp_f4.txt";
    
    int series = distribution(input, F1, F2);
    if (series <= 0) {
        cout << "Ошибка распределения!" << endl;
        return;
    }
    
    while (series > 1) {
        series = mergeFiles(F1, F2, F3, F4);
        copyFile(F3, F1);
        copyFile(F4, F2);
    }
    
    copyFile(F1, output);
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
    
    externalSort(initFile, resultFile);
    
    ifstream res(resultFile);
    cout << "After sorting:" << endl;
    int temp;
    while (res >> temp) {
        cout << temp << " ";
    }
    res.close();
    
    return 0;
}