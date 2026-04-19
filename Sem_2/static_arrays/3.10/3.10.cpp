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
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
               a[i][j] = ((double)rand() / RAND_MAX) * (range_max - range_min) + range_min;  
               cout << a[i][j] << " ";
        }
        cout << endl; 
    }

    for (int i = 0; i < N; i ++){
        for (int j =  i + 1; j < N; j++){
            tmp = a[i][j];
            a[i][j] = a[j][i]; 
            a[j][i] = tmp; 
        }
    }

    for (int i = 0; i < N; i++){
        for(int j = 0; j<N; j++){
            cout << a[i][j] << " "; 
        }
        cout << endl;
    }
}