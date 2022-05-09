#ifndef STORAGE_H
#define STORAGE_H

#include "Product.h"

class Storage
{
private:
    Product*** products;
    int sections;
    int sectionNumber;
    const int shelves = 6;
    const int sequenceNumbers = 10;

    void copy(const Storage& rhs);
public:
    Storage();
    Storage(const Storage& rhs);
    Storage& operator=(const Storage& rhs);
    ~Storage();

    void displayInformation() const;
    void addProduct();
    void removeProduct();
    void referenceInformation(const Date& firstDate, const Date& secondDate);
    void cleanUp(const Date& currentDate);
};

#endif STORAGE_H
