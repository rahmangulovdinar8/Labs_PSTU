#include <iostream> 
#include <cstdlib>
#include <ctime>
using namespace std; 
int main(){
    srand(time(0));
    int range_min = -1000;
    int range_max = 1000; 
    int N; 
    int maxarr = -1000; 
    int minarr = 1000;  
    cin >> N;
    int a[N];
    for (int i = 0; i < N; i++)
    {
        a[i] = ((double)rand() / RAND_MAX) * (range_max - range_min) + range_min;
        cout << a[i] << " ";
    }   
    cout << endl;
    for(int i = 0; i < N; i++){
        if (a[i] > maxarr){ maxarr = a[i];}
        else if (a[i] < minarr) {minarr = a[i];}
    }
    cout << "max = " << maxarr << "; min = " << minarr << endl;
}