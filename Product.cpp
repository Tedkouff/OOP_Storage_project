#include "Product.h"

Product::Product(const MyString& productName, const Date& expireDate, const Date& entryDate, const MyString& manufacturerName,
                 const std::size_t& quantity, const Location& productLocation, const MyString& description)
{
    if(productName == "")
        throw std::invalid_argument("Product name cannot be empty!\n");
    this->productName = productName;

    if(manufacturerName == "")
        throw std::invalid_argument("Manufacturer name cannot be empty!\n");
    this->manufacturerName = manufacturerName;

    // description can be empty
    this->description = description;

    if(quantity < 1)
        throw std::invalid_argument("Quantity cannot be less than 1!\n");
    this->quantity = quantity;

    this->entryDate = entryDate;
    this->expireDate = expireDate;

    this->productLocation = productLocation;
}

Product::Product(const Product& rhs)
{
    copy(rhs);
}

Product& Product::operator=(const Product& rhs)
{
    if(this != &rhs)
        copy(rhs);

    return *this;
}

MyString Product::getProductName() const
{
    return productName;
}

Date Product::getExpireDate() const
{
    return expireDate;
}

Date Product::getEntryDate() const
{
    return entryDate;
}

MyString Product::getManufacturerName() const
{
    return manufacturerName;
}

std::size_t Product::getQuantity() const
{
    return quantity;
}

Location Product::getProductLocation() const
{
    return productLocation;
}

MyString Product::getDescription() const
{
    return description;
}

std::ostream& operator<<(std::ostream& os, const Product& product)
{
    os << "Product Name: " << product.getProductName() << std::endl;
    os << "Expire Date(YYYY.MM.DD): " << product.getExpireDate() << std::endl;
    os << "Entry Date(YYYY.MM.DD): " << product.getEntryDate() << std::endl;
    os << "Manufacturer Name: " << product.getManufacturerName() << std::endl;
    os << "Quantity: " << product.getQuantity() << std::endl;
    os << "Location in storage: " << product.getProductLocation().getSection() << " section, "
                                  << product.getProductLocation().getShelf() << "shelf, "
                                  << product.getProductLocation().getSequenceNumber() << "sequence number"
                                  << std::endl;
    os << "Description: " << product.getDescription() << std::endl;

    return os;
}

Product &Product::copy(const Product &rhs) {
    // validation not needed because rhs is already created
    this->productName = rhs.productName;
    this->manufacturerName = rhs.manufacturerName;
    this->description = rhs.description;
    this->quantity = rhs.quantity;
    this->entryDate = rhs.entryDate;
    this->expireDate = rhs.expireDate;
    this->productLocation = rhs.productLocation;

    return *this;
}

