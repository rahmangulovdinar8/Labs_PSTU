#include <iostream> 
#include <cmath>
using namespace std; 
int main(){
    int N; 
    float x, factorial, sum;
    cin >> N >> x; 
    sum = 1 + x; 
    factorial = 1;

    for (int i = 2; i <= N; i++){
        factorial *= i; 
        sum += (pow(x, i) / factorial); 
    }
    cout << sum << endl; 
}