#include <iostream>
using namespace std;
int main()
{
    int n, tmp, max;
    cout << "Введите длину последовательности" << endl;
    cin >> n;

    cout << endl;
    cin >> max;
    for (int i = 2; i <= n; i++)
    {
        cout << endl;
        cin >> tmp;
        if (tmp > max) { max = tmp; }

    }
    cout << max << endl;
}