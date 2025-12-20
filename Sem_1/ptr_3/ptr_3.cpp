#include <iostream>

using namespace std;

int main() {
    float a, b, sum;
    float *ptr_a, *ptr_b;
    ptr_a = &a;
    ptr_b = &b;

    cin >> a >> b;

    sum = *ptr_a + *ptr_b;

    cout << "Sum: " << sum << endl;

    return 0;
}