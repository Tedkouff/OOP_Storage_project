#ifndef SHELF_H
#define SHELF_H

#include "Product.h"
#include "Vector_Class/Vector.cpp"

class Storage;

class Shelf {
private:
	Product productOnShelf;
	Vector<Date> entryDates;
	Vector<int> productsForEveryDate;

	void setProduct(const Product&);    // мутатор за продукта на рафта
public:
    // конструктори
	Shelf();
	Shelf(const Product&, const Vector<Date>&, const Vector<int>&);

	void add(int, const Date&);                 // добавя продукти към рафта
	void print() const ;				        // извежда информация за продукта на рафта
	const Product& getProductOnShelf() const ;	// функция за достъп
	void save(std::ofstream&);                  // функция за запазване на информация в изходен файлов поток
	void load(std::ifstream&);                  // функция за извличане на информация от входен файлов поток

    // приятелски клас
	friend class Storage;
};

#endif // SHELF_H
