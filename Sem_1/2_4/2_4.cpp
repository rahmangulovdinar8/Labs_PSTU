#include <iostream> 
using namespace std;
int main(){
    int N; 
    cin >> N; 
    int sp = N/2; 
    int st = 1; 
    if (N%2 == 0, N<3){
        cout << "Нельзя вводить четное число и число, меньшее 3" << endl; 
    }
    else{
        for (int i = 0; i < (N+1)/2; i++){
        for (int j = 0; j < sp; j++){
            cout << " "; 
        }
        sp --; 
        for (int j = 0; j < st; j++){
            cout << "*";
        }
        st += 2; 
        cout << endl;
        }
    }
}