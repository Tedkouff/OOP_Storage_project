#include "Date.h"

Date::Date():year(0), month(0), day(0) {}

Date::Date(const int y, const int m, const int d)
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

Date& Date::operator=(const char* date)
{
    year = (date[0] - 48) * 1000 + (date[1] - 48) * 100 + (date[2] - 48) * 10 + (date[3] - 48);
    month = (date[5] - 48) * 10 + (date[6] - 48);
    day = (date[8] -48) * 10 + (date[9] - 48);

    return *this;
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

int Date::getYear() const
{
    return year;
}

int Date::getMonth() const
{
    return month;
}

int Date::getDay() const
{
    return day;
}

bool Date::isValidDate() const
{
    if(month==0 || month>12 || day==0 || day>31) return false; // проверка дали денят и месецът са валидни

    switch (month) // допълнителна проверка за валидността на дните във всеки месец
    {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return true;
        case 4: case 6: case 9: case 11:
            return day <= 30;
        case 2:
            return day <= 28 + leapYear(year);
    }

    return false;
}

bool Date::isValidDate(const int y, const int m, const int d) const
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

bool Date::operator==(const Date& rhs) const
{
    return year == rhs.year && month == rhs.month && day == rhs.day;
}

bool Date::operator<(const Date& rhs) const
{
    if(year < rhs.year)
        return true;
    else {
        if (month < rhs.month)
            return true;
        else{
            if(day < rhs.day)
                return true;
        }
    }

    return false;
}
bool Date::operator>(const Date& rhs) const
{
    return !(*this < rhs);
}

bool Date::leapYear(const int y) const
{
    return (y%4==0 && y%100!=0) || y%400==0;
}

std::istream& operator>>(std::istream& is, Date& date)
{
    int year, day, month;

    is >> year >> month >> day;
    if(!date.isValidDate(year, month, day))
        std::cerr << "That date does not exist!\n";
    else {
        date.year = year;
        date.month = month;
        date.day = day;
    }

    return is;
}

std::ostream &operator<<(std::ostream &os, const Date &date)
{
    os << date.getYear() << "." << date.getMonth() << "." << date.getDay();

    return os;
}
