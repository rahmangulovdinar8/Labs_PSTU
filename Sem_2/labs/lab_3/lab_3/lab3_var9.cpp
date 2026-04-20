#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    double a = 0.1, b = 0.8;
    double eps = 0.0001;
    double step = (b - a) / 10.0;
    int n_fixed = 3;
    
    cout << fixed << setprecision(6);
    cout << "X\t\tSN\t\tSE\t\tY" << endl;
    
    for (double x = a; x <= b + step/2; x += step) {
        double sum_n = 0.0;
        for (int k = 0; k <= n_fixed; k++) {
            sum_n += pow(x, 4*k + 1) / (4*k + 1);
        }
        
        double sum_eps = 0.0;
        double term = x;
        int k = 0;
        while (fabs(term) >= eps) {
            sum_eps += term;
            k++;
            term = term * x * x * x * x * (4*k - 3) / (4*k + 1);
        }
        
        double y = 0.25 * log((1 + x) / (1 - x)) + 0.5 * atan(x);
        
        cout << x << "\t" << sum_n << "\t" << sum_eps << "\t" << y << endl;
    }
    
    return 0;
}