#ifndef SECTION_H
#define SECTION_H

#include "Vector.cpp"
#include "Shelf.h"

class Storage;

class Section {
private:
	MyString name;
	Vector<Shelf> shelves;

	void setName(const MyString&);
public:
	Section();
	Section(const MyString&, const Vector<Shelf>&);
	Section(const char*, const Vector<Shelf>&);

	void print() const;			  // извежда информация за секцията
	const String& getName() const;          // функция за достъп
	const Vector<Shelf>& getShelves() const;// функция за достъп
	void save(std::ofstream&); // функция за запазване на информация в изходен файлов поток
	void load(std::ifstream&); // функция за извличане на информация от входен файлов поток

	friend class Storage; // складът е приятелски клас със секцията
};

#endif // SECTION_H
