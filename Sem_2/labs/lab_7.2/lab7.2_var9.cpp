#include <iostream>
#include <cstdarg>
using namespace std;

double max(char type, int count, ...) {
    va_list args;
    va_start(args, count);
    
    double max_val;
    
    if (type == 'i') {
        int val = va_arg(args, int);
        max_val = val;
        for (int i = 1; i < count; i++) {
            val = va_arg(args, int);
            if (val > max_val) max_val = val;
        }
    } else {
        double val = va_arg(args, double);
        max_val = val;
        for (int i = 1; i < count; i++) {
            val = va_arg(args, double);
            if (val > max_val) max_val = val;
        }
    }
    
    va_end(args);
    return max_val;
}

int main() {
    cout << max('i', 5, 10, 25, 3, 44, 7) << endl;
    cout << max('d', 10, 1.5, 2.7, 0.3, 4.8, 9.1, 2.2, 7.4, 5.5, 3.3, 6.6) << endl;
    cout << max('i', 12, 100, 95, 87, 112, 45, 67, 89, 123, 56, 78, 90, 101) << endl;
    
    return 0;
}