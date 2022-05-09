#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
#include <cstring>
#include <stdexcept>


class MyString
{
private:
    char* str;
    std::size_t lenght;

public:
    MyString();
    MyString(const char* str);
    ~MyString();
    MyString(const MyString& str);
    MyString& operator= (const MyString& str);
    char& operator[](std::size_t pos);
    const char& operator[](std::size_t pos) const;
    std::size_t size() const;
    
    MyString& operator+=(const MyString& rhs);
    MyString operator+(const MyString& rhs) const;
    const char* c_str() const;
    bool operator==(const MyString &rhs) const;
    bool operator== (const char* str) const;

    friend std::ostream& operator<< (std::ostream& os, const MyString& str);
    friend std::istream& operator>> (std::istream& is, MyString &str);
};


#endif //MYSTRING_H
