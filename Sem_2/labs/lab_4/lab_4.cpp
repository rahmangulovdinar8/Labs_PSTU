#include <iostream> 
#include <cstdlib>
#include <ctime>
using namespace std;
#include <locale>

int main() {
    setlocale(LC_ALL, "RUS");
    srand(time(0));
    const int Size = 100;
    int n;
    cout << "Введите длину массива: ";
    cin >> n;
    int a[Size];
    int range_min = -1000;
    int range_max = 1000;
    
    for (int i = 0; i < n; i++)
    {
        a[i] = ((double)rand() / RAND_MAX) * (range_max - range_min) + range_min;
        cout << a[i] << " ";
    }
    cout << endl;
    int valueDelete;
    cout << "Введите значение для удаления: ";
    cin >> valueDelete;
    int indexDelete = -1;
    for (int i = 0; i < n; i++)
    {
        if (a[i] == valueDelete)
        {
            indexDelete = i;
            break;
        }
    }
    if (indexDelete != -1)
    {
        
        for (int i = indexDelete; i < n - 1; i++)
        {
            a[i] = a[i + 1];
        }
        n--; 
        
        for (int i = 0; i < n; i++)
        {
            cout << a[i] << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "элемент со значением " << valueDelete << " не найден в массиве" << endl;
    }
    int k;
    cout << "Введите количество сдвига вправо: ";
    cin >> k;
    k = k % n;
    if (k > 0)
    {
        
        int a2[Size] = {0};

        
        for (int i = 0; i < k; i++)
        {
            a2[i] = a[n - k + i];
        }

        
        for (int i = n - 1; i >= k; i--)
        {
            a[i] = a[i - k];
        }

        
        for (int i = 0; i < k; i++)
        {
            a[i] = a2[i];
        }
       
    }
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    
}