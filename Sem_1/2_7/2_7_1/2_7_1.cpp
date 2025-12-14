#include <iostream>
#include <cmath> 
using namespace std;
int main(){
    int N, k; 
    cin >> N; 
    k = sqrt(N); 
    for(int i = 0; i < k; i++){ 
        for (int j = 0; j < k; j++){
            cout << "* ";
        }
        cout << endl;
    }
}