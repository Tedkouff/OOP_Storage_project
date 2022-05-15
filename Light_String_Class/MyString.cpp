#include "MyString.h"

void MyString::copyStrings(const char* arr_, const int capacity_, const int size_) {
    str = new(std::nothrow) char[strlen(arr_) + 1];
    if (str == nullptr) {
        throw ("No memory for string!(String::copyStrings())");
        return;
    }
    strcpy(str, arr_);
    capacity = capacity_;
    size = size_;
}

void MyString::deleteString() {
    if (str != nullptr) delete[] str;
}

MyString::MyString() {
    str = new(std::nothrow) char[1];
    if (str == nullptr) {
        throw ("No memory for string!(default constructor)");
    }
    capacity = 1;
    size = 0;
}

MyString::MyString(const char* arr_, const int capacity_, const int size_) {
    copyStrings(arr_, capacity_, size_);
}

MyString::MyString(const MyString& other) {
    copyStrings(other.str, other.capacity, other.size);
}

MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        deleteString();
        copyStrings(other.str, other.capacity, other.size);
    }
    return *this;
}

MyString& MyString::operator=(const char* str_) {
    deleteString();
    int l = strlen(str_);
    this->str = new(std::nothrow) char[l + 1];
    if (this->str == nullptr) {
        throw ("No memory for string!(operator=(const char*))");
    }
    for (int i = 0; i < l; i++) {
        this->str[i] = str_[i];
    }
    this->str[l] = '\0';
    capacity = l + 1;
    size = l;
    return *this;
}

MyString::~MyString() {
    deleteString();
}

std::istream& operator>>(std::istream& in, MyString& str) { // vuvejdane simvol po simvol
    char letter;
    int br = 2;
    in.get(letter);
    while (letter != '\n') {
        char* tempArr = new(std::nothrow) char[br];
        if (tempArr == nullptr) {
            throw ("No memory for string!(operator>>)");
            return in;
        }
        if (br == 2) {
            tempArr[0] = letter;
            tempArr[1] = '\0';
        }
        else {
            strcpy(tempArr, str.str);
            tempArr[br - 2] = letter;
            tempArr[br - 1] = '\0';
        }
        str.deleteString();
        str.str = new(std::nothrow) char[br];
        if (str.str == nullptr) {
            delete[] tempArr;
            throw ("No memory for string!(operator>>)");
            return in;
        }
        strcpy(str.str, tempArr);
        br++;
        delete[] tempArr;

        in.get(letter);
    }
    str.capacity = br - 1;
    str.size = br - 2;
    return in;
}

std::ostream& operator<<(std::ostream& out, const MyString& str){
    int i = 0;
    while (str.str[i]) {
        out << str.str[i];
        i++;
    }
    return out;
}

std::ifstream& operator>>(std::ifstream& iFile, MyString& str) {
    char letter;
    int br = 2;
    iFile.get(letter);
    while (letter != '\n') {
        char* tempArr = new(std::nothrow) char[br];
        if (tempArr == nullptr) {
            throw ("No memory for string!(operator>>)");
            return iFile;
        }
        if (br == 2) {
            tempArr[0] = letter;
            tempArr[1] = '\0';
        }
        else {
            strcpy(tempArr, str.str);
            tempArr[br - 2] = letter;
            tempArr[br - 1] = '\0';
        }
        str.deleteString();
        str.str = new(std::nothrow) char[br];
        if (str.str == nullptr) {
            delete[] tempArr;
            throw ("No memory for string!(operator>>)");
            return iFile;
        }
        strcpy(str.str, tempArr);
        br++;
        delete[] tempArr;

        iFile.get(letter);
    }
    str.capacity = br - 1;
    str.size = br - 2;
    return iFile;
}

std::ofstream& operator<<(std::ofstream& oFile, const MyString& str) {
    int i = 0;
    while (str.str[i]) {
        oFile << str.str[i];
        i++;
    }
    return oFile;
}


char& MyString::operator[](const int i){ // dostup do element ot stringa
    if (i <= size && i >= 0) {
        return str[i];
    }
}

int MyString::getCapacity() const{
    return capacity;
}

int MyString::getSize() const{
    return size;
}

void MyString::clear() {
    delete[] str;
    str = new(std::nothrow) char[1];
    if (str == nullptr) {
        throw ("No memory for string!(MyString::clear())");
        return;
    }
    capacity = 1;
    size = 0;
}

bool MyString::operator==(const MyString& other) const{
    if (size != other.getSize()) return false;
    if (strcmp(str, other.str) == 0) return true;
    else return false;
}

bool MyString::operator==(const char* str) const {
    if (size != strlen(str)) return false;
    if (strcmp(str, str) == 0) return true;
    else return false;
}

bool MyString::operator!=(const MyString& other) const {
    return !(*this == other);
}

bool MyString::operator!=(const char* str) const {
    return !(*this == str);
}

MyString& MyString::operator+=(const MyString& other) {
    if (size == 0) { // ako pruviyat string e prazen
        deleteString();
        int len = strlen(other.str);
        str = new(std::nothrow) char[len + 1];
        if (str == nullptr) {
            throw ("No memory for string!(operator+=)");
        }
        for (int i = 0; i < len; i++) {
            str[i] = other.str[i];
        }
        str[len] = '\0';
        size = len;
        capacity = len + 1;
    }
    else {
        int len1 = strlen(str);
        int len2 = strlen(other.str);
        char* tempArr = new(std::nothrow) char[len1 + 1];
        if (tempArr == nullptr) {
            throw ("No memory for string!(operator+=)");
        }
        strcpy(tempArr, str);
        delete[] str;
        str = new(std::nothrow) char[len1 + len2 + 1];
        if (str == nullptr) {
            delete[] tempArr;
            throw ("No memory for string!(operator+=)");
        }
        for (int i = 0; i < len1; i++) str[i] = tempArr[i];
        int br = 0;
        for (int i = len1; i < len1 + len2; i++) {
            str[i] = other.str[br];
            br++;
        }
        str[len1 + len2] = '\0';
        size += other.size;
        capacity += other.capacity;
        delete[] tempArr;
    }
    return *this;
}

MyString& MyString::to_string(const int num) {
    int br = 0, tempNum1 = num, tempNum2 = num;
    while (tempNum1 > 0) {
        tempNum1 /= 10;
        br++;
    }
    char* numStr;
    if (br == 0) {
        numStr = new(std::nothrow) char[br + 2];
        if (numStr == nullptr) {
            throw ("No memory for string!(MyString::to_string())");
        }
    }
    else numStr = new(std::nothrow) char[br + 1];
    if (numStr == nullptr) {
        throw ("No memory for string!(MyString::to_string())");
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

const char *MyString::c_str() const {
    return str;
}
