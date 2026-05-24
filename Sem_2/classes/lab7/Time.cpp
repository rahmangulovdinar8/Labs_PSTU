#include "Time.h"
#include <iostream>
using namespace std;

Time::Time() {
    min = 0;
    sec = 0;
}

Time::Time(int m, int s) {
    min = m;
    sec = s;
    if (sec >= 60) {
        min += sec / 60;
        sec %= 60;
    }
}

Time::Time(const Time& t) {
    min = t.min;
    sec = t.sec;
}

Time::~Time() {}

int Time::getMin() const { return min; }
int Time::getSec() const { return sec; }
void Time::setMin(int m) { min = m; }
void Time::setSec(int s) { sec = s; }

Time& Time::operator=(const Time& t) {
    if (this != &t) {
        min = t.min;
        sec = t.sec;
    }
    return *this;
}

bool Time::operator==(const Time& t) const {
    return (min == t.min && sec == t.sec);
}

bool Time::operator<(const Time& t) const {
    if (min < t.min) return true;
    if (min == t.min && sec < t.sec) return true;
    return false;
}

bool Time::operator>(const Time& t) const {
    if (min > t.min) return true;
    if (min == t.min && sec > t.sec) return true;
    return false;
}

Time Time::operator+(const Time& t) const {
    int totalSec = (min * 60 + sec) + (t.min * 60 + t.sec);
    return Time(totalSec / 60, totalSec % 60);
}

Time Time::operator/(int k) const {
    int totalSec = min * 60 + sec;
    if (k != 0) {
        totalSec /= k;
    }
    return Time(totalSec / 60, totalSec % 60);
}

ostream& operator<<(ostream& out, const Time& t) {
    out << t.min << ":";
    if (t.sec < 10) out << "0";
    out << t.sec;
    return out;
}

istream& operator>>(istream& in, Time& t) {
    cout << "Минуты: ";
    in >> t.min;
    cout << "Секунды: ";
    in >> t.sec;
    if (t.sec >= 60) {
        t.min += t.sec / 60;
        t.sec %= 60;
    }
    return in;
}