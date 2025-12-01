#include <iostream> 
using namespace std;
int main(){
    int S, N, a, b; 
    cin >> N; 
    while (N != 0){
        b = 1;
        a = 2*N;
        while (a >= N){
            b = b * a; 
            a -= 1; 
        }
        S = S + b;
        N = N - 1; 
    }
    cout << S << endl; 
    return 0; 
}

int n; 
int t, s = 0; 