#include <iostream>
using namespace std;

int fibonacci(unsigned int n) {
    if (n == 1 || n == 2) {
        return 1;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    unsigned int num;
    cin >> num;
    cout << fibonacci(num) << endl;
	return 0;
}