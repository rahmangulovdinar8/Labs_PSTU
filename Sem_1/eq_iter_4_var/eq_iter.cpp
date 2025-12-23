//f(x) = 0.25*pow(x,3) + x - 1.2502 [0; 2], E = 0,000001 
//f'(x) = 0.75*pow(x,2) + 1
//f'(a) = 1
//f'(b) = 4 
//lambda = -1/4
#include <iostream> 
#include <cmath> 
using namespace std;
int main(){
    float x,x0;
    double e = 0.000001, lambda = -0.25; 
    x = 0; 
    x0 = 2; 
    while (abs(x-x0) > e){ 
        x0 = x; 
        x = lambda * (0.25 * pow(x0,3) + x0 - 1.2502) + x0;
    }
    cout << "Root: " << x << endl;
    return 0; 
} 