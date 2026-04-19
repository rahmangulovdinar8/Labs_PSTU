#include <iostream>
#include <cmath>
using namespace std;
// a_n = 10^n / n!
int main() {
    double eps = 10000;
    double sum = 0.0;
    double a_n = 1.0;
    int n = 0;
    
    while (fabs(a_n) >= eps) {
        sum += a_n;
        cout << "n=" << n << " a_n=" << a_n << " sum=" << sum << endl;
        
        n++;
        a_n = a_n * 10.0 / n;
    }
    
    
    cout << "Сумма ряда: " << sum << endl;
    cout << "Количество членов: " << n << endl;
    
    return 0;
}