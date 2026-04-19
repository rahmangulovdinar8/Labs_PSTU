#include <iostream>
using namespace std;
int main()
{
    const int N = 11;
    int tmp, p, q;
    int a[N] = { 21, 68, 11, 10, 60, 85, 57, 76, 10, 67, 19 };
    cout << "введите p и q" << endl;
    cin >> p >> q;
    for (int i = 0; i < N; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    while (p < q)
    {
        tmp = a[p];
        a[p] = a[q];
        a[q] = tmp;
        p++;
        q--;
    }
    for (int i = 0; i < N; i++)
    {
        cout << a[i] << " ";
    }
    return 0;
}