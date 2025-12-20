#include <iostream>

using namespace std;

int main() {
    int n;
    float a, max, min;
    float * ptr_a;

    cout << "Enter count numbers: ";
    cin >> n;
    cout << "Enter number: ";
    cin >> a;
    ptr_a = &a;

    min = *ptr_a;
    max = min;

    for (int i = 2; i <= n; i++) {
        cout <<"Enter number: ";
        cin >> a;
        
        if (*ptr_a < min) {
            min = *ptr_a;
        }
        else if (*ptr_a > max) {
            max = *ptr_a;
        }
    }

    cout << "Max: " << max << " Min: " << min << endl;

    return 0;
}