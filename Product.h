#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include "Date.h"

class Product
{
    char* productName;
    Date expireDate;
    Date entryDate;
    char* manufacturerName;
    std::size_t quantity;
    Location productLocation;
    char* description;

public:
    Product(const char* productName, const Date expireDate, const Date entryDate, const char* manufacturerName,
            const std::size_t& quantity, const Location& productLocation, const char* comment);
    Product(const Product& rhs);
    Product& operator=(const Product& rhs);

    char* getProductName() const;
    Date getExpireDate() const;
    Date getEntryDate() const;
    char* getManufacturerName() const;
    std::size_t getQuantity() const;
    Location getProductLocation() const;
    char* getDescription() const;

    friend std::ostream& operator<<(std::ostream& os, const Product& product);
    friend std::istream& operator>>(std::istream& is, Product& product);
};

#endif //PRODUCT_H
