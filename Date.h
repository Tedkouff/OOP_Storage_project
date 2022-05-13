#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <stdexcept>

class Date
{
    unsigned long year;
    unsigned short month;
    unsigned short day;

    bool leapYear(const int y) const;
public:
    Date();
    Date(const int y, const int m, const int d);
    Date(const Date& rhs);
    Date& operator=(const Date& rhs);

    int getYear() const;
    int getMonth() const;
    int getDay() const;

    bool isValidDate() const;
    bool isValidDate(const int y, const int m, const int d) const;

    bool operator==(const Date& rhs) const;
    bool operator<(const Date& rhs) const;
    bool operator>(const Date& rhs) const;

    // оператори за вход и изход
    friend std::istream& operator>>(std::istream&, Date&);
    friend std::ostream& operator<<(std::ostream& os, const Date& date);
};

#endif //DATE_H
