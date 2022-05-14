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
    MyString();                                     // default constructor
    MyString(const char* str);                      // constructor with parameter
    ~MyString();                                    // destructor
    MyString(const MyString& str);                  // copy constructor
    MyString& operator= (const MyString& str);      // copy assignment operator

    char& operator[](std::size_t pos);              // оператор за достъп до елемент намиращ се на позиция pos
    const char& operator[](std::size_t pos) const;  //
    MyString& operator+=(const MyString& rhs);      // оператор за конкатенация на низове
    MyString operator+(const MyString& rhs) const;  //
    bool operator==(const MyString &rhs) const;     // оператор, проверяващ дали два символни низа са еднакви
    bool operator== (const char* str) const;        //

    MyString& num_to_str(const int num);            // връща число като символен низ
    std::size_t size() const;                       // дължина на низа
    void clear();                                   // изчиства съдържанието на низа
    const char* c_str() const;                      // връща указател към null-terminated масив, който има съдържание
                                                    // идентично с това на низа

    // оператори за вход и изход
    friend std::ostream& operator<< (std::ostream& os, const MyString& str);
    friend std::istream& operator>> (std::istream& is, MyString &str);
};

#endif //MYSTRING_H