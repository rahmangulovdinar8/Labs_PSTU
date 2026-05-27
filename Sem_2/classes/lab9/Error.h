#pragma once
#include <iostream>
#include <string>
using namespace std;

class Error {
public:
    virtual void what() {}
    virtual ~Error() {}
};

class SizeError : public Error {
protected:
    string msg;
public:
    SizeError() { msg = "Ошибка размера!\n"; }
    virtual void what() { cout << msg; }
};

class MaxSizeError : public SizeError {
private:
    string msg_;
public:
    MaxSizeError() {
        SizeError();
        msg_ = "Размер превышает MAX_SIZE (20)!\n";
    }
    virtual void what() { cout << msg << msg_; }
};

class EmptySizeError : public SizeError {
private:
    string msg_;
public:
    EmptySizeError() {
        SizeError();
        msg_ = "Множество пустое!\n";
    }
    virtual void what() { cout << msg << msg_; }
};

class IndexError : public Error {
protected:
    string msg;
public:
    IndexError() { msg = "Ошибка индекса!\n"; }
    virtual void what() { cout << msg; }
};

class IndexError1 : public IndexError {
private:
    string msg_;
public:
    IndexError1() {
        IndexError();
        msg_ = "Индекс меньше 0!\n";
    }
    virtual void what() { cout << msg << msg_; }
};

class IndexError2 : public IndexError {
private:
    string msg_;
public:
    IndexError2() {
        IndexError();
        msg_ = "Индекс больше размера множества!\n";
    }
    virtual void what() { cout << msg << msg_; }
};