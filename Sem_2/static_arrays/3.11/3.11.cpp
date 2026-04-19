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
    int a[N][N];
    for (int i = 0; i < N; i++){
        for (int j = 0; j<N; j++){
               a[i][j] = ((double)rand() / RAND_MAX) * (range_max - range_min) + range_min;  
               cout << a[i][j] << " ";
        }
        cout << endl; 
    }

    for (int i = 0; i < N; i++){
        a[i][i] = 0; 
    }

    for (int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << a[i][j] << " "; 
        }
        cout << endl;
    }
}