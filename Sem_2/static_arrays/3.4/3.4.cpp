#include <iostream>
using namespace std;
int main()
{
    const int N = 7;
    int a[N] = { 1, 4, 7, 9, 11, 16, 21};
    bool sorted = true;
    for (int i = 1; i < N; i++)
    {
        if (a[i] < a[i-1])
        {
            sorted = false;
        }
    }
    
    if (sorted == true)
    { 
        cout << "good array" << endl; 
    }
    else 
    { 
        cout << "bad array" << endl; 
    }
    return 0;
}