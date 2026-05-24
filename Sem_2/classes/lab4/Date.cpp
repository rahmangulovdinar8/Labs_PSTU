#include "Date.h"
#include <iostream>
using namespace std;

Date::Date() : Pair() {
    year = 2000;
    month = 1;
    day = 1;
}

Date::Date(int y, int m, int d) : Pair(m, d) {
    year = y;
    month = m;
    day = d;
}

Date::Date(const Date& dt) : Pair(dt) {
    year = dt.year;
    month = dt.month;
    day = dt.day;
}

Date::~Date() {}

int Date::getYear() const { return year; }
int Date::getMonth() const { return month; }
int Date::getDay() const { return day; }
void Date::setYear(int y) { year = y; }
void Date::setMonth(int m) { month = m; }
void Date::setDay(int d) { day = d; }

Date& Date::operator=(const Date& dt) {
    if (this != &dt) {
        Pair::operator=(dt);
        year = dt.year;
        month = dt.month;
        day = dt.day;
    }
    return *this;
}

bool Date::operator==(const Date& dt) const {
    return (year == dt.year && month == dt.month && day == dt.day);
}

bool Date::operator<(const Date& dt) const {
    if (year < dt.year) return true;
    if (year > dt.year) return false;
    if (month < dt.month) return true;
    if (month > dt.month) return false;
    return day < dt.day;
}

bool Date::operator>(const Date& dt) const {
    return !(*this == dt) && !(*this < dt);
}

ostream& operator<<(ostream& out, const Date& dt) {
    out << dt.day << "." << dt.month << "." << dt.year;
    return out;
}

istream& operator>>(istream& in, Date& dt) {
    cout << "Год: ";
    in >> dt.year;
    cout << "Месяц: ";
    in >> dt.month;
    cout << "День: ";
    in >> dt.day;
    return in;
}