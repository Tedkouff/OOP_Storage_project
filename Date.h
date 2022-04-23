#ifndef DATE_H
#define DATE_H

#include <iostream>

class Date
{
    int year;
    int month;
    int day;

    bool isValidDate(const int& year, const int& month, const int& day);
public:
    Date(const int& year, const int& month, const int& day);
    Date(const Date& rhs);
    Date& operator=(const Date& rhs);
    ~Date();

    int getYear() const;
    int getMonth() const;
    int getDay() const;

    friend std::ostream& operator<<(std::ostream& os, const Date& date);
    friend std::istream& operator>>(std::istream& is, Date& date);
};

#endif //DATE_H
