#include "MyString.h"


MyString::MyString()
{
    lenght=0;
    str = new char[lenght + 1];
    str[0] = '\0';
}

MyString::MyString(const char* str)
{
    lenght=strlen(str);
    this->str = new char[lenght + 1];

    strcpy(this->str,str);
    this->str[lenght]='\0';
}

MyString::~MyString() { delete [] str; }

MyString::MyString(const MyString& str)
{
    lenght = str.lenght;
    this->str = new char[lenght+1];
    strcpy(this->str,str.str);
}

MyString& MyString::operator= (const MyString& str1)
{
    if (this != &str1)
    {
        delete str;
        lenght = strlen(str1.str);
        str = new char[lenght+1];
        strcpy(str,str1.str);
        str[lenght]='\0';
    }

    return *this;
}


char& MyString::operator[](std::size_t pos)
{
    return str[pos];
}
const char& MyString::operator[](std::size_t pos) const
{
    return str[pos];
}

MyString &MyString::num_to_str(const int num)
{
    int br = 0, tempNum1 = num, tempNum2 = num;
    while (tempNum1 > 0) {
        tempNum1 /= 10;
        br++;
    }
    char* numStr;
    if (br == 0) {
        numStr = new(std::nothrow) char[br + 2];
        if (numStr == nullptr) {
            throw std::runtime_error("No memory for string!(MyString::num_to_str())");
        }
    }
    else numStr = new(std::nothrow) char[br + 1];
    if (numStr == nullptr) {
        throw std::runtime_error("No memory for string!(MyString::num_to_str())");
    }
    for (int i = 0; i < br; i++) {
        numStr[br - i - 1] = tempNum2 % 10 + '0';
        tempNum2 /= 10;
    }
    if (br == 0) {
        numStr[0] = '0';
        numStr[1] = '\0';
    }
    else numStr[br] = '\0';

    *this = numStr;
    delete[] numStr;

    return *this;
}

std::size_t MyString::size() const
{
    return lenght;
}

void MyString::clear() {
    delete[] str;
    str = nullptr;
    lenght = 0;
}

MyString& MyString::operator+=(const MyString& rhs)
{
    int temp = size() + rhs.size();
    char* newStr = new char[temp + 1];

    for (int i = 0; i < size(); i++)
    {
        newStr[i]=str[i];
    }
    int i,j=0;
    for (i = size(); i < temp; i++)
    {
        newStr[i]=rhs[j];
        j++;
    }

    newStr[temp]='\0';

    *this = MyString(newStr);
    delete [] newStr;

    return *this;
}

MyString MyString::operator+(const MyString& rhs) const
{
    int temp = size() + rhs.size();
    char* newStr = new char[temp + 1];

    strcpy(newStr,str);
    strcat(newStr,rhs.str);
    newStr[temp]='\0';

    MyString tempStr{newStr};

    delete [] newStr;
    return tempStr;
}

bool MyString::operator== (const MyString& rhs) const
{
    if (strcmp(str, rhs.str) == 0)  return true;
    return false;
}

bool MyString::operator== (const char* rhs) const
{
    if(strcmp(str,rhs) == 0) return true;
    return false;
}

const char* MyString::c_str() const
{
    return str;
}

std::ostream& operator<< (std::ostream& os, const MyString& str)
{
    if (str.str)
    {
        for (int i = 0; i < str.lenght; ++i)
        {
            os<<str.str[i];
        }
    }
    return os;
}

std::istream & operator>> (std::istream & is, MyString &str)
{
    char newStr[1024];
    is >> newStr;

    if (str.str) {
        delete str.str;
        str.str = nullptr;
    }

    str.str = new char[strlen(newStr) + 1];
    strcpy(str.str, newStr);
    str.str[strlen(newStr)]= '\0';

    return is;
}
