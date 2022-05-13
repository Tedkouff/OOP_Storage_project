#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <fstream>

#include "Light_String_Class/MyString.h"
#include "Date.h"

class Storage;
class Shelf;

class Product
{
    MyString productName;
    Date expireDate;
    Date entryDate;
    MyString manufacturerName;
    int quantity;
    MyString description;

    Product& copy(const Product& rhs);
public:
    // конструктори
    Product();
    Product(const MyString& productName, const Date& expireDate, const Date& entryDate,
            const MyString& manufacturerName, const int& quantity, const MyString& description);
    Product(const Product& rhs);
    Product& operator=(const Product& rhs);

    // методи за достъп
    MyString getProductName() const;
    Date getExpireDate() const;
    Date getEntryDate() const;
    MyString getManufacturerName() const;
    int getQuantity() const;
    MyString getDescription() const;

    // оператори за работа с файлове
    friend std::ifstream& operator>>(std::ifstream& ifs, Product& product);
    friend std::ofstream& operator<<(std::ofstream& ofs, const Product& product);
    friend std::istream& operator>>(std::istream& is, Product& product);
    friend std::ostream& operator<<(std::ostream& os, const Product& product);

    void save(std::ofstream& ofs); // метод за запазване на информация в изходен файлов поток
    void load(std::ifstream& ifs); // метод за извличане на информация от входен файлов поток

    // приятелски класове на Product
    friend class Shelf;
    friend class Storage;
};

#endif //PRODUCT_H
