#ifndef STORAGE_H
#define STORAGE_H

#include <ctime>

#include "Section.h"
#include "Log.h"

class Storage
{
private:
    Vector<Section> sections;
    Vector<Log> logs;	// промените по склада(логовете) се следят през целия живот на програмата

    void fillShelves(int quantity, const Product& tempProduct, Vector<Shelf>& tempShelves); // запълва рафтове с даден продукт
	void addAndFillNewSections(int numOfNewSections, const Product& tempProduct,
                               Vector<Section>& tempSections, const Date& date); // добавя и запълва секции с даден продукт
   	Date createCurrDate() const;    // създава дата, която е текущата за компютъра
public:
    // конструктори
    Storage();
    Storage(const Vector<Section>& sections, const Vector<Log>& logs);

    void displayInformation() const;        // извежда информация за наличните продукти в склада
    void add(Vector<Section>&);             // добавя нов продукт в диалогов режим
    void removeProduct(Vector<Section>&);   // премахва продукт в диалогов режим
    void printLogs(const char* firstDate, const char* secondDate) const;
                                            // извежда справка за промените по наличността на склада в дадения период
    void cleanUp(Vector<Section>&);         // разчиства склада от продукти с изтекъл срок на годност

    void open(const char*, Vector<Section>&);			// отваря и прочита информация от файл
    void close(Vector<Section>&) const;					// затваря файл и изчиства прочетеното(промените)
    void save(const char*, Vector<Section>&) const;		// запазва новите данни за склада в текущо отворения файл
    void saveAs(const char*, Vector<Section>&) const;	// запазва новите данни за склада в нов, посочен от нас файл
    void help() const;									// извежда информация за поддържаните команди
};

#endif //STORAGE_H