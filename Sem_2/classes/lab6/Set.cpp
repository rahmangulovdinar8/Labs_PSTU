#include "Set.h"
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
    beg.elem = 0;
    end.elem = 0;
}

Set::Set(int s, int k) {
    size = s;
    data = new int[size];
    for (int i = 0; i < size; i++) {
        data[i] = k;
    }
    beg.elem = &data[0];
    end.elem = &data[size];
}

Set::Set(const Set& a) {
    size = a.size;
    data = new int[size];
    for (int i = 0; i < size; i++) {
        data[i] = a.data[i];
    }
    beg.elem = &data[0];
    end.elem = &data[size];
}

Set::~Set() {
    delete[] data;
    data = 0;
}

Set& Set::operator=(const Set& a) {
    if (this == &a) return *this;
    size = a.size;
    if (data != 0) delete[] data;
    data = new int[size];
    for (int i = 0; i < size; i++) {
        data[i] = a.data[i];
    }
    beg.elem = &data[0];
    end.elem = &data[size];
    return *this;
}

int& Set::operator[](int index) {
    if (index < size && index >= 0) {
        return data[index];
    }
    cout << "\nError! Index out of range" << endl;
    return data[0];
}

int Set::operator()() const {
    return size;
}

Set Set::operator+(const Set& a) {
    Set result;
    result.size = 0;
    result.data = new int[size + a.size];
    
    for (int i = 0; i < size; i++) {
        if (!result.contains(data[i])) {
            result.data[result.size++] = data[i];
        }
    }
    
    for (int i = 0; i < a.size; i++) {
        if (!result.contains(a.data[i])) {
            result.data[result.size++] = a.data[i];
        }
    }
    
    int* temp = new int[result.size];
    for (int i = 0; i < result.size; i++) {
        temp[i] = result.data[i];
    }
    delete[] result.data;
    result.data = temp;
    result.beg.elem = &result.data[0];
    result.end.elem = &result.data[result.size];
    
    return result;
}

bool Set::operator==(const Set& a) const {
    if (size != a.size) return false;
    for (int i = 0; i < size; i++) {
        if (data[i] != a.data[i]) return false;
    }
    return true;
}

bool Set::operator!=(const Set& a) const {
    return !(*this == a);
}

ostream& operator<<(ostream& out, const Set& a) {
    out << "{ ";
    for (int i = 0; i < a.size; i++) {
        out << a.data[i];
        if (i < a.size - 1) out << ", ";
    }
    out << " }";
    return out;
}

istream& operator>>(istream& in, Set& a) {
    cout << "Введите " << a.size << " элементов множества:" << endl;
    for (int i = 0; i < a.size; i++) {
        cout << "Элемент " << i + 1 << ": ";
        in >> a.data[i];
    }
    return in;
}