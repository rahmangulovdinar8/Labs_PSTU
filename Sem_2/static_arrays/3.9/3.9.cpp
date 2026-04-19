#include <iostream> 
#include <cstdlib>
#include <ctime>
using namespace std; 
int main(){
    srand(time(0));
    int range_min = -1000;
    int range_max = 1000; 
    int N;  
    cin >> N;
    int j = 0; 
    int a[N], b[N];

    for (int i = 0; i < N; i++){
            a[i] = ((double)rand() / RAND_MAX) * (range_max - range_min) + range_min;  
            cout << a[i] << " ";
        }
    cout << endl; 

    for(int i =0; i < N; i++){
        if (a[i] % 2 == 0){
            b[j] = a[i]; 
            j++;
        }
    }

    for (int i = 0; i < j; i++){
        cout << b[i] << " ";
    }
}