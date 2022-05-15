#ifndef MYSTRING_H
#define MYSTRING_H

#include<iostream>
#include<fstream>
#include<cstring>
#include<exception>


class MyString {
private:
    char* str;
    int capacity;
    int size;

    void copyStrings(const char*, const int, const int);
    void deleteString();
public:
    // конструктори
    MyString();
    MyString(const char*, const int, const int);
    MyString(const MyString&);
    MyString& operator=(const MyString&);
    MyString& operator=(const char*); // operator= za niz
    ~MyString();

    // оператори за вход и изход
    friend std::istream& operator>>(std::istream&, MyString&);
    friend std::ostream& operator<<(std::ostream&, const MyString&);
    friend std::ifstream& operator>>(std::ifstream&, MyString&);
    friend std::ofstream& operator<<(std::ofstream&, const MyString&);

    // логически оператори
    char& operator[](const int);
    bool operator==(const MyString&) const;
    bool operator==(const char*) const;
    bool operator!=(const MyString&) const;
    bool operator!=(const char*) const;
    MyString& operator+=(const MyString&);

    MyString& to_string(const int); // конвентира цяло число в низ
    const char* c_str() const;      // връща указател към null-terminated масив, който има съдържание
                                    // идентично с това на низа
    int getCapacity() const;
    int getSize() const;
    void clear(); // изчиства стринга
};

#endif //MYSTRING_H