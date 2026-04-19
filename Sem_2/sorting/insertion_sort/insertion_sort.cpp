#include <iostream>
using namespace std;
int main()
{
    const int N = 7;
    int key;
    int a[N] = { 3, 5, 11, 0, 6, 7, 14 };
    for (int i = 0; i < N; i++){
        cout << a[i] << " ";
    }
    cout << endl;
    
    for (int i = 1; i < N; i++){
        key = a[i];
        int j = i-1;
        while (j >= 0 && a[j] > key)
        {
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = key;
    }

    for (int i = 0; i < N; i++){
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}