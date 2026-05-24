#include "Pair.h"
#include <iostream>
using namespace std;

class Date : public Pair {
private:
    int year;
    int month;
    int day;
    
public:
    Date();
    Date(int, int, int);
    Date(const Date&);
    ~Date();
    
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    void setYear(int);
    void setMonth(int);
    void setDay(int);
    
    Date& operator=(const Date&);
    bool operator==(const Date&) const;
    bool operator<(const Date&) const;
    bool operator>(const Date&) const;
    
    friend ostream& operator<<(ostream&, const Date&);
    friend istream& operator>>(istream&, Date&);
};