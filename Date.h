#ifndef DATE_H_
#define DATE_H_
#include <iostream>
#include <ctime>

class Date {
private:
    int year;
    char month[3];
    char day[3];

public:
    Date();
    Date(const int, const char*, const char*);
    Date& operator=(const char*);

    // методи за достъп
    const int getYear() const;
    const char* getMonth() const;
    const char* getDay() const;

    // логически оператори
    bool operator==(const Date&) const;
    bool operator<(const Date&) const;
    bool operator>(const Date&) const;
    bool operator<=(const Date&) const;
    bool operator>=(const Date&) const;

    bool isValid() const; // проверка за валидна дата

    // оператори за вход и изход
    friend std::istream& operator>>(std::istream&, Date&);
    friend std::ostream& operator<<(std::ostream&, const Date&);
};

#endif // DATE_H_
