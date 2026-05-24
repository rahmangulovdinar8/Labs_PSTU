#pragma once
#include <iostream>
#include <cmath>
using namespace std;

class Point {
private:
    double first;
    double second;

public:
    void Init(double x, double y) {
        first = x;
        second = y;
    }
    
    void Read() {
        cout << "Введите x: ";
        cin >> first;
        cout << "Введите y: ";
        cin >> second;
    }
    
    void Show() {
        cout << "Точка (" << first << "; " << second << ")" << endl;
    }
    
    double distance() {
        return sqrt(first * first + second * second);
    }
    
    double distance(double x1, double y1) {
        return sqrt((first - x1) * (first - x1) + (second - y1) * (second - y1));
    }
};
