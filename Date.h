#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <stdexcept>

class Date
{
    unsigned long year;
    unsigned short month;
    unsigned short day;

    bool leapYear(unsigned long y) const;
    bool isValidDate(unsigned long y, unsigned short m, unsigned short d) const;
public:
    Date(unsigned long y, unsigned short m, unsigned short d);
    Date(const Date& rhs);
    Date& operator=(const Date& rhs);

    unsigned long getYear() const;
    unsigned short getMonth() const;
    unsigned short getDay() const;

    friend std::ostream& operator<<(std::ostream& os, const Date& date);
    friend std::istream& operator>>(std::istream& is, Date& date);
};

#endif //DATE_H
