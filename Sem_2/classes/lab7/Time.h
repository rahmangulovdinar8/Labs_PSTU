#pragma once
#include <iostream>
using namespace std;

class Time {
private:
    int min;
    int sec;
    
public:
    Time();
    Time(int, int);
    Time(const Time&);
    ~Time();
    
    int getMin() const;
    int getSec() const;
    void setMin(int);
    void setSec(int);
    
    Time& operator=(const Time&);
    bool operator==(const Time&) const;
    bool operator<(const Time&) const;
    bool operator>(const Time&) const;
    Time operator+(const Time&) const;
    Time operator/(int) const;
    
    friend ostream& operator<<(ostream&, const Time&);
    friend istream& operator>>(istream&, Time&);
};