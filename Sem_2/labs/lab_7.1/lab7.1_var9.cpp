#include <iostream>
using namespace std;

struct Fraction {
    int num;
    int den;
};

double add(double a, double b) {
    return a + b;
}

Fraction add(Fraction f1, Fraction f2) {
    Fraction res;
    res.num = f1.num * f2.den + f2.num * f1.den;
    res.den = f1.den * f2.den;
    return res;
}

int main() {
    cout << "3.5 + 2.5 = " << add(3.5, 2.5) << endl;
    
    Fraction a = {1, 2};
    Fraction b = {1, 3};
    Fraction c = add(a, b);
    
    cout << "1/2 + 1/3 = " << c.num << "/" << c.den << endl;
    
    return 0;
}