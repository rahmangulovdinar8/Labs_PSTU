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
    int tmp;
    int k; 
    cin >> k; 
    if (k >= N) { k = N-1;}
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
               a[i][j] = ((double)rand() / RAND_MAX) * (range_max - range_min) + range_min;  
               cout << a[i][j] << " ";
        }
        cout << endl; 
    }

    for (int i = 0; i < N-1; i++){
        for (int j = 0; j < N - 1 - i; j++){
            if (a[k][j] > a[k][k+1]){
                for (int r =0; r < N; r++){ 
                    tmp = a[r][j]; 
                    a[r][j] = a[r][j+1]; 
                    a[r][j+1] = tmp;
                }
            }
        }
    }

    for (int i = 0; i < N; i++){
        for(int j = 0; j<N; j++){
            cout << a[i][j] << " "; 
        }
        cout << endl;
    }
}