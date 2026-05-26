#pragma once
#include <iostream>
using namespace std;

const int MAX_SIZE = 20;

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
    Set(int s);
    Set(int s, int* mas);
    Set(const Set& v);
    ~Set();

    const Set& operator=(const Set& v);
    int operator[](int i) const;
    bool operator!=(const Set& v) const;
    bool operator<(int val) const;

    Iterator first() { return beg; }
    Iterator last() { return end; }

    friend ostream& operator<<(ostream& out, const Set& v);
    friend istream& operator>>(istream& in, Set& v);
};
