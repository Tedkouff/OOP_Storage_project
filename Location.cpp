#include "Location.h"

Location::Location():section(0), shelf(0), sequenceNumber(0) {}

Location::Location(const int& section, const int& shelf, const int& sequenceNumber): section(section), shelf(shelf), sequenceNumber(sequenceNumber) {}

int Location::getSection() const
{
    return section;
}

int Location::getShelf() const
{
    return shelf;
}
int Location::getSequenceNumber() const
{
    return sequenceNumber;
}
