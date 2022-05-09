#ifndef LOCATION_H
#define LOCATION_H

class Location
{
    int section;
    int shelf;
    int sequenceNumber;

public:
    Location();
    Location(const int& section, const int& shelf, const int& sequenceNumber);

    int getSection() const;
    int getShelf() const;
    int getSequenceNumber() const;
};

#endif //LOCATION_H
