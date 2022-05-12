#include "Shelf.h"

Shelf::Shelf() {}

Shelf::Shelf(const Product& product, const Vector<Date>& entryDates, const Vector<int>& productsForEveryDate) 
{
	this->productOnShelf = product;
	this->entryDates = entryDates;
	this->productsForEveryDate = productsForEveryDate;
}

const Product& Shelf::getProductOnShelf() const
{
	return productOnShelf;
}

void Shelf::add(int amount, const Date& date) 
{
	if (this->productOnShelf.amount + amount > 50) { 
		std::cout << "Too much products to add on shelf!" << std::endl;
		return;
	}
	this->productOnShelf.amount += amount; // добавя се количеството към продукта на рафта
	int n = entryDates.size(); 
	bool flag = false;
	for (int i = 0; i < n; i++) {
		if (this->entryDates[i] == date) { // проверява дали датата на внос е срещната във вектора от дати
			flag = true;
			this->productsForEveryDate[i] += amount; // добавяме към количеството, отговарящо за съответната дата
			break;
		}
	}
	if (!flag) { // случай, при който датата на внос е нова за вектора от дати
		this->entryDates.add(date);
		this->productsForEveryDate.add(amount);
	}
	
}

void Shelf::print() const 
{
  // to be updated
}

void Shelf::setProduct(const Product& otherProduct) 
{
	productOnShelf = otherProduct;
}

void Shelf::save(std::ofstream& oFile)
{
	productOnShelf.save(oFile);
	int sizeOfEntryDates = entryDates.size();
	oFile << sizeOfEntryDates << std::endl;
	for (int i = 0; i < sizeOfEntryDates; i++) {
		oFile << entryDates[i] << " " << productsForEveryDate[i] << std::endl;
	}
}

void Shelf::load(std::ifstream& iFile)
{
	productOnShelf.load(iFile);
	int sizeOfEntryDates;
	iFile >> sizeOfEntryDates;
	for (int i = 0; i < sizeOfEntryDates; i++) {
		Date tempDate;
		iFile >> tempDate;
		entryDates.add(tempDate);
		iFile.ignore();
		int tempNum;
		iFile >> tempNum;
		productsForEveryDate.add(tempNum);
		iFile.ignore();
	}
}
