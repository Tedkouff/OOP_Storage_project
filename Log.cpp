#include "Log.h"

Log::Log() {}

Log::Log(const Date& date, const MyString& message)
{
    this->dateOfLog = date;
    this->message = message;
}

Log::Log(const Date& date, const char* message)
{
    this->dateOfLog = date;
    this->message = message;
}

const Date& Log::getDate() const
{
    return dateOfLog;
}

const MyString& Log::getMessage() const
{
    return message;
}

std::istream& operator>>(std::istream& is, Log& log)
{
    is >> log.dateOfLog;
    is.ignore();
    is.ignore();
    is >> log.message;
    return is;
}

std::ostream& operator<<(std::ostream& os, Log& log)
{
    os << log.dateOfLog << "	" << log.message << std::endl;
    return os;
}
