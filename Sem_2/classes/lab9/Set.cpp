#include "Set.h"
#include "Error.h"
#include <iostream>
using namespace std;

bool Set::contains(int val) const {
    for (int i = 0; i < size; i++) {
        if (data[i] == val) return true;
    }
    return false;
}

Set::Set() {
    size = 0;
    data = 0;
}

Set::Set(int s) {
    if (s > MAX_SIZE) throw MaxSizeError();
    if (s < 0) throw SizeError();
    
    size = s;
    data = new int[size];
    for (int i = 0; i < size; i++) {
        data[i] = 0;
    }
}

Set::Set(int s, int* mas) {
    if (s > MAX_SIZE) throw MaxSizeError();
    if (s < 0) throw SizeError();
    
    size = 0;
    data = new int[s];
    
    for (int i = 0; i < s; i++) {
        if (!contains(mas[i])) {
            data[size++] = mas[i];
        }
    }
    
    int* temp = new int[size];
    for (int i = 0; i < size; i++) {
        temp[i] = data[i];
    }
    delete[] data;
    data = temp;
}

Set::Set(const Set& v) {
    size = v.size;
    data = new int[size];
    for (int i = 0; i < size; i++) {
        data[i] = v.data[i];
    }
}

Set::~Set() {
    if (data != 0) delete[] data;
}

const Set& Set::operator=(const Set& v) {
    if (this == &v) return *this;
    if (data != 0) delete[] data;
    size = v.size;
    data = new int[size];
    for (int i = 0; i < size; i++) {
        data[i] = v.data[i];
    }
    return *this;
}

int Set::operator[](int i) const {
    if (i < 0) throw IndexError1();
    if (i >= size) throw IndexError2();
    return data[i];
}

Set Set::operator+(int a) const {
    if (size + 1 > MAX_SIZE) throw MaxSizeError();
    
    int* temp = new int[size + 1];
    for (int i = 0; i < size; i++) {
        temp[i] = data[i];
    }
    temp[size] = a;
    
    Set result(size + 1, temp);
    delete[] temp;
    return result;
}

Set Set::operator--() {
    if (size == 0) throw EmptySizeError();
    
    if (size == 1) {
        size = 0;
        delete[] data;
        data = 0;
        return *this;
    }
    
    int* temp = new int[size - 1];
    for (int i = 0; i < size - 1; i++) {
        temp[i] = data[i];
    }
    
    delete[] data;
    size--;
    data = temp;
    return *this;
}

ostream& operator<<(ostream& out, const Set& v) {
    if (v.size == 0) {
        out << "{ }";
    } else {
        out << "{ ";
        for (int i = 0; i < v.size; i++) {
            out << v.data[i];
            if (i < v.size - 1) out << ", ";
        }
        out << " }";
    }
    return out;
}

istream& operator>>(istream& in, Set& v) {
    for (int i = 0; i < v.size; i++) {
        cout << "Элемент " << i + 1 << ": ";
        in >> v.data[i];
    }
    return in;
}