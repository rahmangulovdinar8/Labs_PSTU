#include <iostream>
using namespace std;
main(){
    int N, b; 
    cin >> N; 
    if (N == 0){
        cout << "Нельзя посчитать сумму натуральных чисел при N <= 0" << endl;
    }
    while (N!=0){
        b += N;
        N -= 1;
    }
    cout << b << endl; 
}