#pragma once
#include <iostream>
using namespace std;

template<class T>
class Iterator {
    friend class Set<T>;
private:
    T* elem;
public:
    Iterator() { elem = 0; }
    Iterator(const Iterator<T>& it) { elem = it.elem; }
    bool operator==(const Iterator<T>& it) { return elem == it.elem; }
    bool operator!=(const Iterator<T>& it) { return elem != it.elem; }
    void operator++() { ++elem; }
    void operator--() { --elem; }
    T& operator*() const { return *elem; }
};

template<class T>
class Set {
private:
    int size;
    T* data;
    Iterator<T> beg;
    Iterator<T> end;
    
    bool contains(const T& val) const;
    
public:
    Set();
    Set(int s, T k = T());
    Set(const Set<T>& a);
    ~Set();
    
    Set<T>& operator=(const Set<T>& a);
    T& operator[](int index);
    int operator()() const;
    Set<T> operator+(const Set<T>& a);
    
    Iterator<T> first() { return beg; }
    Iterator<T> last() { return end; }
    
    template<class U>
    friend ostream& operator<<(ostream& out, const Set<U>& a);
    
    template<class U>
    friend istream& operator>>(istream& in, Set<U>& a);
};

template<class T>
bool Set<T>::contains(const T& val) const {
    for (int i = 0; i < size; i++) {
        if (data[i] == val) return true;
    }
    return false;
}

template<class T>
Set<T>::Set() {
    size = 0;
    data = 0;
    beg.elem = 0;
    end.elem = 0;
}

template<class T>
Set<T>::Set(int s, T k) {
    size = s;
    data = new T[size];
    for (int i = 0; i < size; i++) {
        data[i] = k;
    }
    beg.elem = &data[0];
    end.elem = &data[size];
}

template<class T>
Set<T>::Set(const Set<T>& a) {
    size = a.size;
    data = new T[size];
    for (int i = 0; i < size; i++) {
        data[i] = a.data[i];
    }
    beg.elem = &data[0];
    end.elem = &data[size];
}

template<class T>
Set<T>::~Set() {
    delete[] data;
    data = 0;
}

template<class T>
Set<T>& Set<T>::operator=(const Set<T>& a) {
    if (this == &a) return *this;
    size = a.size;
    if (data != 0) delete[] data;
    data = new T[size];
    for (int i = 0; i < size; i++) {
        data[i] = a.data[i];
    }
    beg.elem = &data[0];
    end.elem = &data[size];
    return *this;
}

template<class T>
T& Set<T>::operator[](int index) {
    if (index < size && index >= 0) {
        return data[index];
    }
    cout << "\nError! Index out of range" << endl;
    return data[0];
}

template<class T>
int Set<T>::operator()() const {
    return size;
}

template<class T>
Set<T> Set<T>::operator+(const Set<T>& a) {
    Set<T> result;
    result.size = 0;
    result.data = new T[size + a.size];
    
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
    
    T* temp = new T[result.size];
    for (int i = 0; i < result.size; i++) {
        temp[i] = result.data[i];
    }
    delete[] result.data;
    result.data = temp;
    result.beg.elem = &result.data[0];
    result.end.elem = &result.data[result.size];
    
    return result;
}

template<class T>
ostream& operator<<(ostream& out, const Set<T>& a) {
    out << "{ ";
    for (int i = 0; i < a.size; i++) {
        out << a.data[i];
        if (i < a.size - 1) out << ", ";
    }
    out << " }";
    return out;
}

template<class T>
istream& operator>>(istream& in, Set<T>& a) {
    for (int i = 0; i < a.size; i++) {
        in >> a.data[i];
    }
    return in;
}