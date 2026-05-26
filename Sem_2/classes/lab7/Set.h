#pragma once
#include <iostream>
using namespace std;

template<class T>
class Set;

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
    void operator+=(int n) { elem += n; }
    T& operator*() const { return *elem; }
};

template<class T>
class Set {
private:
    int size;
    T* data;
    Iterator<T> beg;
    Iterator<T> end;

    bool contains(const T& val) const {
        for (int i = 0; i < size; i++)
            if (data[i] == val) return true;
        return false;
    }

public:
    Set() {
        size = 0; data = 0; beg.elem = 0; end.elem = 0;
    }

    Set(int s, T k = T()) {
        size = s;
        data = new T[size];
        for (int i = 0; i < size; i++) data[i] = k;
        beg.elem = &data[0];
        end.elem = &data[size];
    }

    Set(const Set<T>& a) {
        size = a.size;
        data = new T[size];
        for (int i = 0; i < size; i++) data[i] = a.data[i];
        beg.elem = &data[0];
        end.elem = &data[size];
    }

    ~Set() {
        if (data != 0) delete[] data;
        data = 0;
    }

    Set<T>& operator=(const Set<T>& a) {
        if (this == &a) return *this;
        if (data != 0) delete[] data;
        size = a.size;
        data = new T[size];
        for (int i = 0; i < size; i++) data[i] = a.data[i];
        beg.elem = &data[0];
        end.elem = &data[size];
        return *this;
    }

    T& operator[](int index) {
        if (index >= 0 && index < size) return data[index];
        cout << "Error! Index out of range" << endl;
        return data[0];
    }

    bool operator!=(const Set<T>& a) const {
        if (size != a.size) return true;
        for (int i = 0; i < size; i++)
            if (data[i] != a.data[i]) return true;
        return false;
    }

    bool operator<(const T& val) const {
        return contains(val);
    }

    Iterator<T> first() { return beg; }
    Iterator<T> last() { return end; }

    friend ostream& operator<<(ostream& out, const Set<T>& a) {
        out << "{ ";
        for (int i = 0; i < a.size; i++) {
            out << a.data[i];
            if (i < a.size - 1) out << ", ";
        }
        out << " }";
        return out;
    }

    friend istream& operator>>(istream& in, Set<T>& a) {
        for (int i = 0; i < a.size; i++) {
            in >> a.data[i];
        }
        return in;
    }
};
