#include <iostream>
using namespace std;
int main()
{
    const int N = 11;
    int max;
    int count = 1;
    int a[N] = { 4, 56, 31, 54, 78, 99, 14, 99, 15, 99, 91 };
    max = a[0];
    cout << a[0] << " ";
    for (int i = 1; i < N; i++)
    {
        cout << a[i] << " ";
        if (a[i] > max)
        {
            max = a[i];
            count = 1;
        }  
        else if (a[i] == max) { count++; }
    }  
    cout << endl;
    cout << "Max: " << max << endl;
    cout << "Количество элементов с этим значением: " << count << endl;
    return 0;
}