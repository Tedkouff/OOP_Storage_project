#ifndef SECTION_H
#define SECTION_H

#include "Vector_Class/Vector.cpp"
#include "Shelf.h"

class Storage;

class Section {
private:
	MyString name;
	Vector<Shelf> shelves;

	void setName(const MyString& name); // мутатор за името на секцията
public:
    // конструктори
	Section();
	Section(const MyString& name, const Vector<Shelf>& shelves);
	Section(const char* name, const Vector<Shelf>& shelves);

    // методи за достъп
	const MyString& getName() const;
	const Vector<Shelf>& getShelves() const;

    void print() const;			          // извежда информация за секцията
	void save(std::ofstream& ofs);        // функция за запазване на информация в изходен файлов поток
	void load(std::ifstream& ifs);        // функция за извличане на информация от входен файлов поток

    // приятелски клас
	friend class Storage;
};

#endif // SECTION_H
