#ifndef LOG_H
#define LOG_H

#include "Date.h"
#include "Light_String_Class/MyString.h"

class Storage;

class Log {
private:
    Date dateOfLog;       // дата на справка
    MyString message;	  // съобщение на справка

public:
    Log();                                  // default constructor
    Log(const Date&, const MyString&);      // constructor with parameters
    Log(const Date&, const char* message);  // constructor with parameters

    // методи за достъп
    const Date& getDate() const;
    const MyString& getMessage() const;

    // методи за вход и изход
    friend std::istream& operator>>(std::istream& is, Log& log);
    friend std::ostream& operator<<(std::ostream& os, Log& log);

    friend class Storage;
};

#endif //LOG_H
