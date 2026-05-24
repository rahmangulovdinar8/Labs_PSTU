#include "Point.h"
#include <iostream>
#include <clocale>
using namespace std;

Point make_point(double x, double y) {
    Point p;
    p.Init(x, y);
    return p;
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    Point p1;
    p1.Read();
    p1.Show();
    cout << "Расстояние до начала координат: " << p1.distance() << endl;
    
    double x, y;
    cout << "\nВведите координаты второй точки: ";
    cin >> x >> y;
    cout << "Расстояние между точками: " << p1.distance(x, y) << endl;
    
    Point* p2 = new Point;
    p2->Init(3.5, 4.5);
    p2->Show();
    cout << "Расстояние до начала координат: " << p2->distance() << endl;
    delete p2;
    
    Point arr[2];
    for (int i = 0; i < 2; i++) {
        cout << "\nТочка " << i+1 << ":\n";
        arr[i].Read();
    }
    cout << "\nМассив точек:\n";
    for (int i = 0; i < 2; i++) {
        arr[i].Show();
    }
    
    Point* p_arr = new Point[2];
    for (int i = 0; i < 2; i++) {
        cout << "\nДинамическая точка " << i+1 << ":\n";
        p_arr[i].Read();
    }
    for (int i = 0; i < 2; i++) {
        p_arr[i].Show();
    }
    delete[] p_arr;
    
    Point p3 = make_point(2.5, 3.5);
    cout << "\nТочка созданная make_point:\n";
    p3.Show();
    
    return 0;
}