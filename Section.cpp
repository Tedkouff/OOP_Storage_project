#include "Section.h"

Section::Section() {}

Section::Section(const MyString& name, const Vector<Shelf>& shelves)
{
	this->name = name;
	this->shelves = shelves;
}

Section::Section(const char* name, const Vector<Shelf>& shelves) 
{
	this->name = name;
	this->shelves = shelves;
}

const MyString& Section::getName() const
{
	return name;
}

const Vector<Shelf>& Section::getShelves() const
{
	return shelves;
}

void Section::setName(const MyString& name)
{
	this->name = name;
}

void Section::print() const {
	std::cout << "Section name: " << name << std::endl;
	int n = shelves.size();
	for (int i = 0; i < n; i++) {
		std::cout << "Number of shelf: " << i << std::endl;
		shelves[i].print();
	}
	std::cout << std::endl;
}

void Section::save(std::ofstream& ofs)
{
    ofs << name << std::endl;
	int n = shelves.size();
    ofs << n << " ";
	for (int j = 0; j < n; j++) {
		shelves[j].save(ofs);
	}
}

void Section::load(std::ifstream& ifs)
{
    ifs.ignore();
    ifs >> name;
	int n;
    ifs >> n;
    ifs.ignore();
	for (int j = 0; j < n; j++) {
		Shelf tempShelf;
		tempShelf.load(ifs);
		shelves.add(tempShelf); 
	}
}
