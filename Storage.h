#ifndef STORAGE_H
#define STORAGE_H

#include "Product.h"

class Storage
{
private:
    Vector<Section> sections;
	// logging class to be created and implemented

	void fillShelves(int, const Product&, Vector<Shelf>&); // запълва рафтове с даден продукт
	void addAndFillNewSections(int, const Product&, Vector<Section>&, const Date&); // добавя и запълва секции с даден продукт
	const Date& createCurrDate() const; // създава дата, която е текущата за компютъра
public:
    Storage();
    // Storage(const Vector<Section>& sections, const Vector<Log>& logs) could be removed
    Storage(const Storage& rhs);
    Storage& operator=(const Storage& rhs);
    ~Storage();

    void displayInformation() const;
    void add(Vector<Section>&);
    void removeProduct(Vector<Section>&);
    void referenceInformation(const Date& firstDate, const Date& secondDate);
    void cleanUp(Vector<Section>&);
};

#endif STORAGE_H
