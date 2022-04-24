#include "Date.h"

Date::Date(unsigned long y, unsigned short m, unsigned short d)
{
    if (!isValidDate(y, m, d))
        throw std::invalid_argument("Invalid input of date!\n");

    this->day=d;
    this->month=m;
    this->year=y;
}

Date::Date(const Date &rhs)
{
    this->day=rhs.day;
    this->month=rhs.month;
    this->year=rhs.year;
}

Date &Date::operator=(const Date &rhs)
{
    if(this != &rhs)
    {
        this->day=rhs.day;
        this->month=rhs.month;
        this->year=rhs.year;
    }

    return *this;
}

unsigned long Date::getYear() const
{
    return year;
}

unsigned short Date::getMonth() const
{
    return month;
}

unsigned short Date::getDay() const
{
    return day;
}

bool Date::isValidDate(unsigned long y, unsigned short m, unsigned short d) const
{
    if(m==0 || m>12 || d==0 || d>31) return false;

    switch (m)
    {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return true;
        case 4: case 6: case 9: case 11:
            return d<=30;
        case 2:
            return d <= 28 + leapYear(y);
    }
    
    return false;
}

bool Date::leapYear(unsigned long y) const
{
    return (y%4==0 && y%100!=0) || y%400==0;
}


std::ostream &operator<<(std::ostream &os, const Date &date)
{
    os << date.getYear() << "-" << date.getMonth() << "-" << date.getDay();

    return os;
}

std::istream &operator>>(std::istream &is, Date &date)
{
    unsigned long year;
    unsigned short day, month;

    is >> year >> month >> day;
    date = Date(year, month, day);

    return is;
}
