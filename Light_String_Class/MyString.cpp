#include "MyString.h"


    MyString::MyString()  /// default constructor
    {
        lenght=0;
        str = new char[lenght + 1];
        str[0] = '\0';
    }

    /// създава нов обект и копира в него съдържанието на str
    MyString::MyString(const char* str)
    {
        lenght=strlen(str);
        this->str = new char[lenght + 1];

        strcpy(this->str,str);
        this->str[lenght]='\0';
    }

    /// destructor
    MyString::~MyString() { delete [] str; }

    /// copy constructor
    MyString::MyString(const MyString& str)
    {
        lenght = str.lenght;
        this->str = new char[lenght+1];
        strcpy(this->str,str.str);
    }

    /// copy assignment operator
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

    /// operator за достъп до елемент намиращ се на позиция pos
    char& MyString::operator[](std::size_t pos)
    {
        return str[pos];
    }
    const char& MyString::operator[](std::size_t pos) const
    {
        return str[pos];
    }

    /// дължина на низа
    std::size_t MyString::size() const
    {
        return lenght;
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

    /// проверява дали два символни низа са еднакви
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

    /// връща указател към null-terminated масив, който има съдържание идентично с това на низа
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
