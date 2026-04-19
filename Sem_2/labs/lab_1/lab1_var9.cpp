#include <iostream>
#include <cmath>
using namespace std;
// ( (a+b)^4 - (a^4 + 4a^3b) ) / ( (a+b)^4 - (a^4 + 4a^3b) ) a = 100 , b = 0.001
int main() {
    int a = 100;
    float b_float = 0.001f;
    double b_double = 0.001;
    
    
    float chisl_float = pow(a + b_float, 4) - (pow(a, 4) + 4 * pow(a, 3) * b_float);
    float znam_float = 6 * pow(a, 2) * pow(b_float, 2) + 4 * a * pow(b_float, 3) + pow(b_float, 4);
    float result_float = chisl_float / znam_float;
    
    
    double chisl_double = pow(a + b_double, 4) - (pow(a, 4) + 4 * pow(a, 3) * b_double);
    double znam_double = 6 * pow(a, 2) * pow(b_double, 2) + 4 * a * pow(b_double, 3) + pow(b_double, 4);
    double result_double = chisl_double / znam_double;
    
    cout << "Результат (float): " << result_float << endl;
    cout << "Результат (double): " << result_double << endl;
    
    int n, m;
    cout << "\nВведите n и m: ";
    cin >> n >> m;
    
    int n1 = n, m1 = m;
    cout << "++n * ++m = " << ++n1 * ++m1 << endl;
    
    int m2 = m;
    cout << "m++ = " << m2++ << endl;
    
    int n3 = n;
    cout << "n++ > m = " << (n3++ > m) << endl;
    
    return 0;
}