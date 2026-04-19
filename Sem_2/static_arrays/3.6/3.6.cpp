#include <iostream> 
#include <cstdlib>
#include <ctime>
using namespace std; 
int main(){
    srand(time(0));
    int range_min = -1000;
    int range_max = 1000; 
    int N, k; 
    cin >> N >> k; 
    int a[N], b[N];
    for (int i = 0; i < N; i++)
    {
        a[i] = ((double)rand() / RAND_MAX) * (range_max - range_min) + range_min;
        cout << a[i] << " ";
    }   
    cout << endl; 

    if ( k > N ){ k = k%N;} 

    for (int i = 0; i < N; i++){
        int K = i - k; 
        if (K < 0) {K+=N;}
        b[K] = a[i]; 
    }    

    for (int i = 0; i < N; i++){
        a[i] = b[i]; 
        cout << a[i] << " ";
    }
}