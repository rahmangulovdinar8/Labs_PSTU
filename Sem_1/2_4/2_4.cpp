#include <iostream> 
using namespace std;
int main(){
    int N; 
    cin >> N; 
    int p = N/2; 
    int t = 1; 
    if (N%2 == 0, N<3){
        cout << "Нельзя вводить четное число и число, меньшее 3" << endl; 
    }
    else{
        for (int i = 0; i < (N+1)/2; i++){
        for (int j = 0; j < p; j++){
            cout << " "; 
        }
        p--; 
        for (int j = 0; j < t; j++){
            cout << "*";
        }
        t += 2; 
        cout << endl;
        }
    }
}
