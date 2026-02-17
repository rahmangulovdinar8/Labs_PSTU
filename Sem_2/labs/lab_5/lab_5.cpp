#include <iostream> 
#include <cstdlib>
#include <ctime>
using namespace std;
#include <locale>
const int Size = 10;
int Sum(int a[][Size], int n)
{
    int s = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i > j) 
            {
                s += a[i][j];
            }
    return s;
}
int main()
{
    srand(time(0));
    int range_min = -1000;
    int range_max = 1000;
    setlocale(LC_ALL, "RUS");
    int n, m;
    cout << "Размер матрицы: "; 
    cin >> n;
    cout << "Количество матриц: "; 
    cin >> m;

    int mat[5][Size][Size] = { 0 };
    int sums[5] = { 0 };

        
    for (int k = 0; k < m; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                mat[k][i][j] = ((double)rand() / RAND_MAX) * (range_max - range_min) + range_min;
                cout << mat[k][i][j] << " ";
            }
            cout << endl; 
        }

        sums[k] = Sum(mat[k], n);
        cout << "Сумма " << k + 1 << ": " << sums[k] << endl << endl;
    }

        
    int max = sums[0];
    for (int k = 1; k < m; k++)
        if (sums[k] > max)
        {
            max = sums[k];
        }
    cout << "Максимальная сумма: " << max << endl;
}