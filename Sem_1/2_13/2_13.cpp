#include <iostream>
#include <cmath>
using namespace std;
int main(){
    float a, b, c, x, x1, D;
    cin >> a >> b >> c; 
    D = pow(b, 2) - 4*a*c;
    if (D > 0){
        x = ((-b) + sqrt(D)) / (2*a); 
        x1 = ((-b) - sqrt(D)) / (2*a);
        cout << "x1 =" << x << "x2 = " << x1 << endl;
    }
    else if (D == 0){
        x = (-b) / (2*a);
        cout << "x= " << x << endl;
    }
    else {cout << "Корней нет" << endl;}
    return 0;
    }