//f(x) = (0.25 * pow(x, 3)) + x - 1.2502) [0; 2], E = 0,000001 
//f'(x) = 0.75*pow(x,2) + 1
//f''(x) = 1,5x
#include <iostream> 
#include <cmath> 
using namespace std;
int main(){ 
    double x, x0;
    x = 2;
    x0 = 0;
    double e = 0.000001;
    while(abs(x-x0) > e)
    {
        x0 = x;
        x = x0 - (((0.25 * pow(x, 3)) + x0 - 1.2502) / ((0.75 * pow(x0, 2)) + 1));
    }
    cout << "Root:" << x << endl;
    return 0; 
 } 
