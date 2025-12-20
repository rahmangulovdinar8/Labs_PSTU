#include <iostream>

using namespace std;

int main() {
    unsigned int n, fact = 1;
    unsigned int * ptr_n;

    cout << "Enter num: ";
    cin >> n;

    ptr_n = &n;

    for (int i = 1; i <= *ptr_n; i++) {
        fact *= i;
    }

    cout << "Factorial: " << fact << endl;

    return 0;
}