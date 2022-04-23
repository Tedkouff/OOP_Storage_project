#ifndef PROJECT_STORAGE_LOCATION_H
#define PROJECT_STORAGE_LOCATION_H

class Location
{
    int section;
    int shelf;
    int serialNumber;

public:
    Location(const int section, const int shelf, const int serialNumber);
};

#endif //PROJECT_STORAGE_LOCATION_H
