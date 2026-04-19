#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int** createMatrix(int rows, int cols) {
    int** mat = new int*[rows];
    for (int i = 0; i < rows; i++) {
        mat[i] = new int[cols];
    }
    return mat;
}

void matrixRandom(int** mat, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mat[i][j] = rand() % 100;
        }
    }
}

void printMatrix(int** mat, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << mat[i][j] << "\t";
        }
        cout << endl;
    }
}

int** addCol(int** mat, int rows, int& cols, int pos) {
    int** newMat = createMatrix(rows, cols + 1);
    for (int i = 0; i < rows; i++) {
        int oldCol = 0;
        for (int j = 0; j < cols + 1; j++) {
            if (j == pos) {
                newMat[i][j] = 0;
            } else {
                newMat[i][j] = mat[i][oldCol++];
            }
        }
    }
    for (int i = 0; i < rows; i++) {
        delete[] mat[i];
    }
    delete[] mat;
    cols++;
    return newMat;
}

void deleteMatrix(int** mat, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] mat[i];
    }
    delete[] mat;
}

int main() {
    srand(time(0));
    int rows, cols, pos;
    cout << "Введите строки: ";
    cin >> rows;
    cout << "Введите столбцы: ";
    cin >> cols;
    int** matrix = createMatrix(rows, cols);
    matrixRandom(matrix, rows, cols);
    cout << "\nИсходный массив:" << endl;
    printMatrix(matrix, rows, cols);
    cout << "\nПозиция для вставки (0-" << cols << "): ";
    cin >> pos;
    if (pos < 0 || pos > cols) {
        cout << "Неверно!" << endl;
        deleteMatrix(matrix, rows);
        return 1;
    }
    matrix = addCol(matrix, rows, cols, pos);
    cout << "\nМассив после вставки:" << endl;
    printMatrix(matrix, rows, cols);
    deleteMatrix(matrix, rows);
    return 0;
}