#include <iostream>
using namespace std;

unsigned int NOD(unsigned int a, unsigned int b) {
    if (a == b) {
        return a;
    }
    else if (a > b) {
        return NOD(a - b, b);
    }
    else {
        return NOD(a, b - a);
    }

}

int main() {
    unsigned int firstNum, secondNum;
    cout << "Enter a and b: ";
    cin >> firstNum >> secondNum;
    if ((firstNum == 0 && secondNum != 0) || (firstNum != 0 && secondNum == 0)) {
        cout << (firstNum > secondNum ? firstNum : secondNum) << endl;
    }
    else if (firstNum == 0 && secondNum == 0) {
        cout << "Error!" << endl;
    }
    else {
        cout << NOD(firstNum, secondNum) << endl;
    }
    return 0;
}