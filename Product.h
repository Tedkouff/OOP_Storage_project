#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include "MyString.h"
#include "Date.h"
#include "Location.h"

class Product
{
    MyString productName;
    Date expireDate;
    Date entryDate;
    MyString manufacturerName;
    std::size_t quantity;
    Location productLocation;
    MyString description;

    Product& copy(const Product& rhs);
public:
    Product(const MyString& productName, const Date& expireDate, const Date& entryDate, const MyString& manufacturerName,
            const std::size_t& quantity, const Location& productLocation, const MyString& description);
    Product(const Product& rhs);
    Product& operator=(const Product& rhs);

    MyString getProductName() const;
    Date getExpireDate() const;
    Date getEntryDate() const;
    MyString getManufacturerName() const;
    std::size_t getQuantity() const;
    Location getProductLocation() const;
    MyString getDescription() const;

    friend std::ostream& operator<<(std::ostream& os, const Product& product);
};

#endif //PRODUCT_H
