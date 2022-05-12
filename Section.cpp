#include "Section.h"

Section::Section() {}

Section::Section(const String& name, const Vector<Shelf>& shelves)
{
	this->name = name;
	this->shelves = shelves;
}

Section::Section(const char* name, const Vector<Shelf>& shelves) 
{
	this->name = name;
	this->shelves = shelves;
}

const String& Section::getName() const
{
	return name;
}

const Vector<Shelf>& Section::getShelves() const
{
	return shelves;
}

void Section::setName(const String& name) 
{
	this->name = name;
}

void Section::print() const {
	std::cout << "Section name: " << name << std::endl;
	int n = shelves.size();
	for (int i = 0; i < n; i++) {
		std::cout << "Number of shelves: " << i << std::endl;
		shelves[i].print();
	}
	std::cout << std::endl;
}

void Section::save(std::ofstream& oFile) 
{
	oFile << name << std::endl;
	int n = shelves.size();
	oFile << n << " ";
	for (int j = 0; j < n; j++) {
		shelves[j].save(oFile); 
	}
}

void Section::load(std::ifstream& iFile) 
{
	iFile.ignore();
	iFile >> name;
	int n;
	iFile >> n;
	iFile.ignore();
	for (int j = 0; j < n; j++) {
		Shelf tempShelf;
		tempShelf.load(iFile);
		shelves.add(tempShelf); 
	}
}
