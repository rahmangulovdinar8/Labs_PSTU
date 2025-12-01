#include <iostream>
using namespace std;
main(){
    int N; int b = 1; 
    cin >> N; 
    if (N <= 0){
        cout << "Нельзя посчитать произведение натуральных чисел при N <= 0" << endl;
    }
    else{
        for (int i = 1; i <= N; i ++){
        b *= i;
        }
    }
    cout << b << endl; 
}