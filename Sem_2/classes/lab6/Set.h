#pragma once
#include <iostream>
using namespace std;

class Iterator {
    friend class Set;
private:
    int* elem;
public:
    Iterator() { elem = 0; }
    Iterator(const Iterator& it) { elem = it.elem; }
    bool operator==(const Iterator& it) { return elem == it.elem; }
    bool operator!=(const Iterator& it) { return elem != it.elem; }
    void operator+=(int n) { elem += n; }
    int& operator*() const { return *elem; }
};

class Set {
private:
    int size;
    int* data;
    Iterator beg;
    Iterator end;

    bool contains(int val) const;

public:
    Set();
    Set(int s, int k = 0);
    Set(const Set& a);
    ~Set();

    Set& operator=(const Set& a);
    int& operator[](int index);
    bool operator!=(const Set& a) const;
    bool operator<(int val) const;

    Iterator first() { return beg; }
    Iterator last() { return end; }

    friend ostream& operator<<(ostream& out, const Set& a);
    friend istream& operator>>(istream& in, Set& a);
};
