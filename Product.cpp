#include "Product.h"

Product::Product():quantity(0) {}

Product::Product(const MyString& productName, const Date& expireDate, const Date& entryDate,
                 const MyString& manufacturerName, const int& quantity, const MyString& description)
{
    this->productName = productName;
    this->expireDate = expireDate;
    this->entryDate = entryDate;
    this->manufacturerName = manufacturerName;
    this->quantity = quantity;
    this->description = description;
}

Product::Product(const char* productName, const char* expireDate, const char* entryDate,
                 const char* manufacturerName, const int quantity, const char* description)
{
    this->productName = productName;
    this->expireDate = expireDate;
    this->entryDate = entryDate;
    this->manufacturerName = manufacturerName;
    this->quantity = quantity;
    this->description = description;
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

int Product::getQuantity() const
{
    return quantity;
}

MyString Product::getDescription() const
{
    return description;
}

Product &Product::copy(const Product &rhs)
{
    this->productName = rhs.productName;
    this->manufacturerName = rhs.manufacturerName;
    this->description = rhs.description;
    this->quantity = rhs.quantity;
    this->entryDate = rhs.entryDate;
    this->expireDate = rhs.expireDate;

    return *this;
}

bool Product::operator==(const Product& other) const
{
    // сравнението е по име, срок на годност и име на производител
    if (productName == other.productName && expireDate == other.expireDate && manufacturerName == other.manufacturerName)
        return true;

    return false;
}

std::ifstream &operator>>(std::ifstream &ifs, Product &product)
{
    ifs >> product.productName;
    ifs >> product.expireDate;
    ifs.ignore();
    ifs >> product.manufacturerName;
    ifs >> product.quantity;
    ifs.ignore();
    ifs >> product.description;
    for (int i = 0; i < 15; i++) ifs.ignore(); // това е за приемните дати

    return ifs;
}

std::ofstream &operator<<(std::ofstream &ofs, const Product &product)
{
    ofs << product.productName << std::endl;
    ofs << product.expireDate << std::endl;
    ofs << product.manufacturerName << std::endl;
    ofs << product.quantity << std::endl;
    ofs << product.description << std::endl;
    ofs << "Entry dates: ";

    return ofs;
}

std::istream &operator>>(std::istream &is, Product &product)
{
    std::cout << "Product name:";
    is >> product.productName;
    int n = product.productName.getSize();
    for (int i = 0; i < n; i++) {
        if ((product.productName[i] < 'a' || product.productName[i] > 'z') &&
            (product.productName[i] < 'A' || product.productName[i] > 'Z') &&
            (product.productName[i] < '0' || product.productName[i] > '9'))
        {
            std::cout << "Invalid name!" << std::endl;
            return is;
        }
    }

    std::cout << "Expire date(YYYY-MM-DD):";
    is >> product.expireDate;
    if (!(product.expireDate.isValid())) return is;
    std::cout<<product.expireDate;

    std::cout << "Entry date(YYYY-MM-DD):";
    is >> product.entryDate;
    if (!(product.entryDate.isValid())) return is;
    if (product.entryDate > product.expireDate) {
        std::cout << "Storage does not take in moldy products!" << std::endl;
        return is;
    }

    is.ignore();
    std::cout << "Manufacturer name:";
    is >> product.manufacturerName;

    std::cout << "Quantity:";
    char validAmount[10];
    is.getline(validAmount, 10);
    n = strlen(validAmount);
    bool flag = true;
    for (int i = 0; i < n; i++) {
        if (validAmount[0] == '0') {
            flag = false;
            break;
        }
        if (validAmount[i] < '0' || validAmount[i]>'9') {
            flag = false;
            break;
        }
    }
    if (!flag) {
        std::cout << "Invalid amount!" << std::endl;
        return is;
    }
    product.quantity = atoi(validAmount);

    std::cout << "Description:";
    is >> product.description;

    return is;
}

std::ostream& operator<<(std::ostream& os, const Product& product)
{
    os << std::endl;
    os << "Product Name: " << product.getProductName() << std::endl;
    os << "Expire Date(YYYY.MM.DD): " << product.getExpireDate() << std::endl;
    os << "Manufacturer Name: " << product.getManufacturerName() << std::endl;
    os << "Quantity: " << product.getQuantity() << std::endl;
    os << "Description: " << product.getDescription() << std::endl;
    os << std::endl;

    return os;
}

void Product::save(std::ofstream &ofs)
{
    ofs << *this;
}

void Product::load(std::ifstream &ifs)
{
    ifs >> *this;
}
