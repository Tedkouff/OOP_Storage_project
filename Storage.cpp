#include "Storage.h"

Storage::Storage() {}

Storage::Storage(const Vector<Section>& sections, const Vector<Log>& logs)
{
    this->sections = sections;
    this->logs = logs;
}

void Storage::displayInformation() const 
{
    if (sections.size() == 0) {
        std::cout << "Storage is empty!" << std::endl;
        std::cout << std::endl;
        return;
    }
    std::cout << "Information about products in storage: " << std::endl;
    int n = sections.size();
    std::cout << "Sections in the storage are " << n << ":" << std::endl;
    for (int i = 0; i < n; i++)
        sections[i].print();
}

void Storage::add(Vector<Section>& tempSections)
{ 
    // при добавяне на продукт, се добавя справка в logs
    Product tempProduct; // продуктът, който ще добавяме
    std::cout << "Enter the product's characteristics: " << std::endl;
    std::cin >> tempProduct;

    if (tempProduct.getDescription().getSize() == 0) return;
    int n = tempSections.size();
    Vector<int> positions;
    bool flag = false;
    for (int i = 0; i < n; i++)
    {
        if (tempProduct.getProductName() == tempSections[i].getName() && tempSections[i].getShelves().size() < 50) {
            positions.add(i); // запазва индекса на секцията с еднакво име с продукта
            flag = true;
        }
    }

    Date dateOfAdding; // дата на добавяне на продукта в склада
    dateOfAdding = tempProduct.getEntryDate();

    if (!flag) { // ако не е намерен такъв продукт
        int numOfNewSections = tempProduct.getQuantity() / 2500 + 1;
        addAndFillNewSections(numOfNewSections, tempProduct, tempSections, dateOfAdding);
    }
    else { // ако продуктът съществува
        int n = positions.size(), j = 0;
        while(tempProduct.getQuantity() > 0 && tempSections[positions[0]].getShelves().size() < 50)
        {
            if (tempProduct == tempSections[positions[0]].getShelves()[j].getProductOnShelf())
            { // ако продуктът, който добавяме e == на този от рафта
                int addedQuantity;
                if (tempProduct.getQuantity() >= 50 - tempSections[positions[0]].getShelves()[j].getProductOnShelf().getQuantity())
                {
                    // добавяното количество е повече от свободното място на рафта
                    addedQuantity = 50 - tempSections[positions[0]].shelves[j].productOnShelf.quantity;
                }
                else
                    addedQuantity = tempProduct.quantity; // добавяното количество е по-малко от свободното място на рафта

                if (addedQuantity > 0)
                {
                    tempSections[positions[0]].shelves[j].productOnShelf.quantity += addedQuantity;
                    bool isNotMet = true;
                    int sizeOfEntryDates = tempSections[positions[0]].shelves[j].entryDates.size();
                    for (int i = 0; i < sizeOfEntryDates; i++)
                    {
                        if (tempSections[positions[0]].getShelves()[j].entryDates[i] == tempProduct.getEntryDate())
                        {
                            tempSections[positions[0]].shelves[j].productsForEveryDate[i] += addedQuantity;
                            //добавяме към вектора, който следи количеството продукт, внесен на определена дата
                            isNotMet = false;
                            break;
                        }
                    }
                    if (isNotMet) { // ако датата на постъпване е нова за вектора от дати
                        tempSections[positions[0]].shelves[j].entryDates.add(tempProduct.getEntryDate());
                        tempSections[positions[0]].shelves[j].productsForEveryDate.add(addedQuantity);
                    }
                    tempProduct.quantity -= addedQuantity; // намалява се количеството на добавяния продукт

                    MyString message, op, numOfSection, numOfShelf, sh, nameOfPr, productStr, quantity, addedQStr;
                    // създава се съобщение за справка за добавяне
                    op = "operation: add | Section: ";
                    numOfSection.to_string(positions[0]);
                    sh = " | Shelf: ";
                    numOfShelf.to_string(j);
                    productStr = " | product: ";
                    nameOfPr = tempProduct.getProductName();
                    quantity = " | quantity: ";
                    addedQStr.to_string(addedQuantity);
                    message += op;
                    message += numOfSection;
                    message += sh;
                    message += numOfShelf;
                    message += productStr;
                    message += nameOfPr;
                    message += quantity;
                    message += addedQStr;

                    Log tempLog(dateOfAdding, message);
                    logs.add(tempLog); // добавя се към вектора от справки
                }
            }
            if (j == tempSections[positions[0]].getShelves().size() - 1 && tempProduct.getQuantity() > 0) {
                // ако са свършили рафтовете за проверка, но са < 50 и количеството на продукта все още не е свършил
                int amountOfNewShelves = tempProduct.getQuantity() / 50 + 1; // количеството нови рафтове, които ще се добавят
                if (amountOfNewShelves <= 50 - tempSections[positions[0]].getShelves().size()) {
                    // ако количеството продукт се побира в останалото място в секцията
                    for (int i = 0; i < amountOfNewShelves - 1; i++) {
                        Shelf tempShelf;
                        Product copyOfTempProduct(tempProduct.getProductName(), tempProduct.getExpireDate(),
                                                  tempProduct.getEntryDate(), tempProduct.getManufacturerName(), 50, tempProduct.getDescription());
                        tempShelf.productOnShelf = copyOfTempProduct;
                        tempShelf.entryDates.add(tempProduct.getEntryDate());
                        tempShelf.productsForEveryDate.add(50);
                        tempSections[positions[0]].shelves.add(tempShelf);

                        MyString message, op, numOfSection, numOfShelf, sh, nameOfPr, productStr, quantity, addedQStr;
                        // създава се съобщение за справка за добавяне
                        op = "operation: add | Section: ";
                        numOfSection.to_string(positions[0]);
                        sh = " | Shelf: ";
                        numOfShelf.to_string(tempSections[positions[0]].getShelves().size());
                        productStr = " | product: ";
                        nameOfPr = tempProduct.getProductName();
                        quantity = " | quantity: ";
                        addedQStr.to_string(50);
                        message += op;
                        message += numOfSection;
                        message += sh;
                        message += numOfShelf;
                        message += productStr;
                        message += nameOfPr;
                        message += quantity;
                        message += addedQStr;

                        Log tempLog(dateOfAdding, message);
                        logs.add(tempLog);
                    }

                    tempProduct.quantity %= 50;
                    Shelf tempShelf;
                    Product copyOfTempProduct(tempProduct.getProductName(), tempProduct.getExpireDate(),
                                              tempProduct.getEntryDate(), tempProduct.getManufacturerName(), tempProduct.getQuantity(), tempProduct.getDescription());
                    tempShelf.productOnShelf = copyOfTempProduct;
                    tempShelf.entryDates.add(tempProduct.getEntryDate());
                    tempShelf.productsForEveryDate.add(tempProduct.getQuantity());
                    tempSections[positions[0]].shelves.add(tempShelf);

                    MyString message, op, numOfSection, numOfShelf, sh, nameOfPr, productStr, quantity, addedQStr;
                    // създава се съобщение за справка за добавяне
                    op = "operation: add | Section: ";
                    numOfSection.to_string(positions[0]);
                    sh = " | Shelf: ";
                    numOfShelf.to_string(tempSections[positions[0]].getShelves().size());
                    productStr = " | product: ";
                    nameOfPr = tempProduct.getProductName();
                    quantity = " | quantity: ";
                    addedQStr.to_string(tempProduct.getQuantity());
                    message += op;
                    message += numOfSection;
                    message += sh;
                    message += numOfShelf;
                    message += productStr;
                    message += nameOfPr;
                    message += quantity;
                    message += addedQStr;

                    Log tempLog(dateOfAdding, message);
                    logs.add(tempLog);

                    tempProduct.quantity = 0;
                }
                else {
                    // ако не се побира в тази секция
                    int shelvesToBeAdded = 50 - tempSections[positions[0]].getShelves().size();
                    for (int i = 0; i < shelvesToBeAdded; i++) {
                        Shelf tempShelf;
                        Product copyOfTempProduct(tempProduct.getProductName(), tempProduct.getExpireDate(),
                                                  tempProduct.getEntryDate(), tempProduct.getManufacturerName(), 50, tempProduct.getDescription());
                        tempShelf.productOnShelf = copyOfTempProduct;
                        tempShelf.entryDates.add(tempProduct.getEntryDate());
                        tempShelf.productsForEveryDate.add(50);
                        tempSections[positions[0]].shelves.add(tempShelf);

                        MyString message, op, numOfSection, numOfShelf, sh, nameOfPr, productStr, quantity, addedQStr;
                        // създава се съобщение за справка за добавяне
                        op = "operation: add | Section: ";
                        numOfSection.to_string(positions[0]);
                        sh = " | Shelf: ";
                        numOfShelf.to_string(tempSections[positions[0]].getShelves().size());
                        productStr = " | product: ";
                        nameOfPr = tempProduct.getProductName();
                        quantity = " | quantity: ";
                        addedQStr.to_string(50);
                        message += op;
                        message += numOfSection;
                        message += sh;
                        message += numOfShelf;
                        message += productStr;
                        message += nameOfPr;
                        message += quantity;
                        message += addedQStr;

                        Log tempLog(dateOfAdding, message);
                        logs.add(tempLog);
                    }
                    tempProduct.quantity -= shelvesToBeAdded * 50;
                }

                break;
            }
            j++;
        }
        if (tempProduct.getQuantity() > 0) { // ако са свършили секции в склада, но все още има продукт за добавяне
            int numOfNewSections = tempProduct.getQuantity() / 2500 + 1;
            addAndFillNewSections(numOfNewSections, tempProduct, tempSections, dateOfAdding);
        }
    }
    std::cout << "Product added successfully!" << std::endl;
    std::cout << std::endl;
}

void Storage::removeProduct(Vector<Section>& tempSections)
{
    MyString nameOfProduct;
    int amountOfProduct;
    std::cout << "product: ";
    std::cin >> nameOfProduct;
    std::cout << "\namount: ";
    std::cin >> amountOfProduct;
    if (amountOfProduct == 0) return;

    Date dateOfRemoving; // датата, на която се извършва премахването
    std::cout << "Choose an option for the date that you are removing the products: " << std::endl;
    std::cout << "1: Enter a date that you want." << std::endl;
    std::cout << "2: Remove by current date." << std::endl;

    int option;      // избира се дали датата да е текущата за компютъра или да е въведена от потребителя
    std::cout << "Option(1 / 2): ";
    std::cin >> option;
    if (option == 1) {
        std::cout << "Enter date: ";
        std::cin >> dateOfRemoving;
    }
    else if (option == 2)
        dateOfRemoving = createCurrDate();
    else {
        std::cerr << "Incorrect option!" << std::endl;
        std::cout << std::endl;
        return;
    }

    int amountOfAvailableProducts = 0, n = tempSections.size();

    for (int i = 0; i < n; i++) {
        if (tempSections[i].getName() == nameOfProduct) {
            int numOfShelves = tempSections[i].getShelves().size();
            for (int j = 0; j < numOfShelves; j++) {
                amountOfAvailableProducts += tempSections[i].getShelves()[j].getProductOnShelf().getQuantity();
            } // сумира се цялото налично количество за продукт
        }
    }
    if (amountOfAvailableProducts == 0) { // ако в склада не съществува такъв продукт
        std::cerr << "There's no such product in the storage!" << std::endl;
        std::cout << std::endl;
        return;
    }
    if (amountOfAvailableProducts < amountOfProduct)
    { // ако потребителят е избрал да премахне повече количество, отколкото има в склада
        std::cout << "The inputed quantity is more than the available." << std::endl;
        std::cout << "Available quantity of the product: " << amountOfAvailableProducts << std::endl;
        std::cout << "Batches: ";
        for (int i = 0; i < n; i++) {
            if (tempSections[i].getName() == nameOfProduct) {
                int numOfShelves = tempSections[i].getShelves().size();
                for (int j = 0; j < numOfShelves; j++) {
                    std::cout << tempSections[i].getShelves()[j].getProductOnShelf().getExpireDate() << ", ";
                    // извеждат се сроковете на годност на наличните продукти (от вида на премахвания)
                }
            }
        }

        // избира се опция дали да има промяна по склада или не
        std::cout << "\n1. I'll still remove the remaining products." << std::endl;
        std::cout << "2. Exit the command." << std::endl;
        std::cout << "Option(1 / 2): ";
        int option;
        std::cin >> option;

        if (option == 1) {
            for (int i = 0; i < n; i++) {
                if (tempSections[i].getName() == nameOfProduct) {
                    tempSections.removeAtIndex(i); // изтриваме секцията, ако е с продукта, който премахваме
                }
            }
            MyString message, op, nameOfPr, removed;
            // създава се съобщение за справка за премахване
            op = "operation: remove |  product: ";
            nameOfPr = nameOfProduct;
            removed = " | all removed from storage.";
            message += op;
            message += nameOfPr;
            message += removed;

            Log tempLog(dateOfRemoving, message);
            logs.add(tempLog);

            return;
        }
        else if (option == 2) return;
        else {
            std::cerr << "Incorrect option!" << std::endl;
            std::cout << std::endl;
            return;
        }
    }
    else { // наличните продукти са повече, премахване по процедурата
        Vector<Date> expireDates;

        for (int i = 0; i < n; i++)
        { // обхождане по всички секции
            if (tempSections[i].getName() == nameOfProduct)
            {
                int numOfShelves = tempSections[i].getShelves().size();
                for (int j = 0; j < numOfShelves; j++)
                { // обхождане по всички рафтове
                    expireDates.add(tempSections[i].getShelves()[j].productOnShelf.getExpireDate());
                } // добавяме срока на годност на продукта от всеки рафт
            }
        }

        int sizeOfExpiryDates = expireDates.size();
        for (int i = 0; i < sizeOfExpiryDates; i++)
        { // сортиране на временния вектор за срокове на годност във възходящ ред
            for (int j = i + 1; j < sizeOfExpiryDates; j++) {
                if (expireDates[i] > expireDates[j]) {
                    Date tempDate = expireDates[i];
                    expireDates[i] = expireDates[j];
                    expireDates[j] = tempDate;
                }
            }
        }

        int tempAmountOfRemovedProduct = amountOfProduct, br=0;
        while (tempAmountOfRemovedProduct > 0)
        { // докато не се премахне избраното от потребителя количество продукт
            for (int i = 0; i < n; i++)
            { // обхождане по секции
                if (tempAmountOfRemovedProduct <= 0) break;
                if (tempSections[i].getName() == nameOfProduct)
                { // ако секцията е за този продукт
                    int numOfShelves = tempSections[i].getShelves().size();
                    for (int j = 0; j < numOfShelves; j++)
                    { // обхождане по рафтове
                        if (expireDates[br] == tempSections[i].getShelves()[j].getProductOnShelf().getExpireDate())
                        {// от този рафт ще се премахват продукти
                            if (tempAmountOfRemovedProduct <= tempSections[i].shelves[j].productOnShelf.quantity)
                            {// въведеното количество е по-малко от наличното на рафта
                                std::cout << "Section: " << tempSections[i].getName();
                                std::cout << " | shelf: " << j << std::endl;
                                std::cout << "Batch: " << tempSections[i].getShelves()[j].getProductOnShelf().getExpireDate() << " ";
                                std::cout << "Removed product: " << tempAmountOfRemovedProduct << " of " << tempSections[i].getShelves()[j].getProductOnShelf().getQuantity() << std::endl << std::endl;
                                tempSections[i].shelves[j].productOnShelf.quantity -= tempAmountOfRemovedProduct;
                                // премахва се въведеното количество от продукта на рафта
                                if (tempSections[i].shelves[j].productOnShelf.quantity == 0) {
                                    tempSections[i].shelves.removeAtIndex(j);
                                }

                                MyString message, op, numOfSection, sh, numOfShelf, productStr, nameOfPr, amountStr, quantity;
                                // създава се съобщение за справка за премахване
                                op = "operation: remove | Section: ";
                                numOfSection.to_string(i);
                                sh = " | Shelf: ";
                                numOfShelf.to_string(j);
                                productStr = " | product: ";
                                nameOfPr = nameOfProduct;
                                amountStr = " | amount: ";
                                quantity.to_string(tempAmountOfRemovedProduct);
                                message += op;
                                message += numOfSection;
                                message += sh;
                                message += numOfShelf;
                                message += productStr;
                                message += nameOfPr;
                                message += amountStr;
                                message += quantity;

                                Log tempLog(dateOfRemoving, message);
                                logs.add(tempLog);

                                while (tempAmountOfRemovedProduct > 0) {
                                    // оправят се векторите с дати на прием и количество за всяка дата
                                    int count = 0;
                                    if (tempSections[i].shelves[j].productsForEveryDate[0] >
                                        tempAmountOfRemovedProduct) {
                                        tempSections[i].shelves[j].productsForEveryDate[0] -= tempAmountOfRemovedProduct;
                                        tempAmountOfRemovedProduct = 0;
                                    } else if (tempSections[i].shelves[j].productsForEveryDate[0] ==
                                               tempAmountOfRemovedProduct) {
                                        tempSections[i].shelves[j].productsForEveryDate.removeAtIndex(0);
                                        tempSections[i].shelves[j].entryDates.removeAtIndex(0);
                                        tempAmountOfRemovedProduct = 0;
                                    } else {
                                        tempAmountOfRemovedProduct -= tempSections[i].shelves[j].productsForEveryDate[0];
                                        tempSections[i].shelves[j].productsForEveryDate.removeAtIndex(0);
                                        tempSections[i].shelves[j].entryDates.removeAtIndex(0);
                                    }
                                    count++;
                                }

                                tempAmountOfRemovedProduct = 0;
                                break; // премахването е приключило и се спира алгоритъма
                            }
                            else
                            {// въведеното е повече от наличното за рафта
                                std::cout << "Section: " << tempSections[i].getName();
                                std::cout << " | shelf: " << j << std::endl;
                                std::cout << "Batch: " << tempSections[i].getShelves()[j].getProductOnShelf().getExpireDate() << " ";
                                std::cout << "Removed product: " << tempSections[i].getShelves()[j].getProductOnShelf().getQuantity() << " of " << tempSections[i].getShelves()[j].getProductOnShelf().getQuantity() << std::endl << std::endl;
                                tempAmountOfRemovedProduct -= tempSections[i].shelves[j].productOnShelf.quantity;

                                MyString message, op, numOfSection, sh, numOfShelf, productStr, nameOfPr, amountStr, amount_;
                                // създава се съобщение за справка за премахване
                                op = "operation: remove | Section: ";
                                numOfSection.to_string(i);
                                sh = " | Shelf: ";
                                numOfShelf.to_string(j);
                                productStr = " | product: ";
                                nameOfPr = nameOfProduct;
                                amountStr = " | amount: all ";
                                amount_.to_string(tempSections[i].getShelves()[j].getProductOnShelf().getQuantity());
                                message += op;
                                message += numOfSection;
                                message += sh;
                                message += numOfShelf;
                                message += productStr;
                                message += nameOfPr;
                                message += amountStr;
                                message += amount_;

                                Log tempLog(dateOfRemoving, message);
                                logs.add(tempLog);

                                tempSections[i].shelves.removeAtIndex(j);
                            }
                            br++; // преминаване към следващата партида продукти
                        }
                    }
                }
            }
        }

        for (int i = 0; i < n; i++)
        {// премахват се секциите с празни рафтове
            if (tempSections[i].getShelves().size() == 0)
                tempSections.removeAtIndex(i);
        }
    }
}

void Storage::printLogs(const char* firstDate, const char* secondDate) const
{
    std::cout << "References to all changes in storage from " << firstDate << " to " << secondDate  << ": "<< std::endl << std::endl;
    int n = logs.size();
    Date fDate, sDate;
    fDate = firstDate;
    sDate = secondDate;
    if (!(fDate.isValid()) || !(sDate.isValid())) return;
    bool empty = true;
    for (int i = 0; i < n; i++) {
        if (!(fDate > logs[i].getDate()) && !(sDate < logs[i].getDate()))
        { // ако дадата на справката е в дадения период
            std::cout << logs[i];
            empty = false;
        }
    }
    if (empty) std::cout << "Unfortunately, there's no changes in that range." << std::endl;
    std::cout << std::endl;
}

void Storage::cleanUp(Vector<Section>& tempSections)
{
    std::cout << "Choose an option for the date that will be compared with the expiry date: " << std::endl;
    std::cout << "1: Enter a date that you want." << std::endl;
    std::cout << "2: Clear by current date." << std::endl;
    int option; // избира се опция за дата за справката на почистване
    bool cleanedSomething = false;
    std::cout << "Option(1 / 2): ";
    std::cin >> option;
    if (option == 1) {
        Date inputDate;
        std::cout << "Enter date: ";
        std::cin >> inputDate;
        if(!(inputDate.isValid())) return;
        int n = tempSections.size();
        for (int i = 0; i < n; i++) { // цикъл по всички секции
            int numOfShelves = tempSections[i].getShelves().size();
            for (int j = 0; j < numOfShelves; j++) { // обхождане на рафтовете на секциите
                if (inputDate > tempSections[i].getShelves()[j].getProductOnShelf().getExpireDate()) {
                    // ако продуктът е с изтекъл срок на годност
                    tempSections[i].shelves.removeAtIndex(j);
                    j--;
                    numOfShelves--;
                    cleanedSomething = true;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            if (tempSections[i].getShelves().size() == 0) tempSections.removeAtIndex(i);
        }
        if (!cleanedSomething) {
            std::cout << "All products are in date. There was nothing to be cleaned." << std::endl;
            std::cout << std::endl;
            return;
        }
        MyString message;
        // създава се съобщение за справка за почивстване на склада
        message = "operation: clean | Storage cleaned by specified date.";
        Log tempLog(inputDate, message);
        logs.add(tempLog);
    }
    else if (option == 2) {
        Date currDate;
        currDate = createCurrDate(); // създава се текуща дата на компютъра

        int n = tempSections.size();
        for (int i = 0; i < n; i++)
        { // цикъл по всички секции
            int numOfShelves = tempSections[i].getShelves().size();
            for (int j = 0; j < numOfShelves; j++) { // обхождане на всички рафтове в секциите
                if (currDate > tempSections[i].getShelves()[j].getProductOnShelf().getExpireDate())
                { // ако продуктът е с изтекъл срок на годност
                    tempSections[i].shelves.removeAtIndex(j);
                    j--;
                    numOfShelves--;
                    cleanedSomething = true;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            if (tempSections[i].getShelves().size() == 0) tempSections.removeAtIndex(i);
        }
        if (!cleanedSomething) {
            std::cout << "All products are in date. There was nothing to be cleaned." << std::endl;
            std::cout << std::endl;
            return;
        }
        MyString message;
        // създава се съобщение за справка за почивстване на склада
        message = "operation: clean | Storage cleaned by specified date.";
        Log tempLog(currDate, message);
        logs.add(tempLog);
    }
    else {
        std::cerr << "Incorrect option!" << std::endl;
        std::cout << std::endl;
        return;
    }
    std::cout << "Storage cleared successfully!" << std::endl;
    std::cout << std::endl;
}

void Storage::open(const char* dir, Vector<Section>& tempSections)
{	// ще се пазят и логовете във файл logs.txt
    std::ifstream iFile(dir, std::ios::in); // отваря файла за продуктите
    if (!iFile) {                   // ако файлът не съществува, създаваме нов с това име
        std::ofstream oFile(dir);
        int zero = 0;
        oFile << zero;
        oFile.close();
        iFile.open(dir, std::ios::in);
        std::cout << "There was no existing file with that name, but there was created a new empty one!" << std::endl;
        std::cout << std::endl;
    }
    iFile.seekg(0, std::ios::end);
    if (iFile.tellg() == 0)
    { // ако файлът е празен
        iFile.close();
        std::ofstream oFile(dir, std::ios::out);
        if (!oFile) {
            std::cerr << "Failed to open!" << std::endl;
            std::cout << std::endl;
            return;
        }
        int zero = 0;
        oFile << zero; // записва '0'
        oFile.close();
        iFile.open(dir, std::ios::in);
        if (!iFile) {
            std::cerr << "Failed to open!" << std::endl;
            std::cout << std::endl;
        }

    }
    iFile.seekg(0, std::ios::beg);
    tempSections.clear(); // tempSections се трие, когато ще се чете нов файл
    int numOfSections;
    iFile >> numOfSections;
    for (int i = 0; i < numOfSections; i++) { // четем от файла данни за склада
        Section tempSect;
        tempSect.load(iFile);
        tempSections.add(tempSect);
    }

    sections = tempSections;
    std::wcout << "File opened successfully!" << std::endl;
    std::cout << std::endl;
}

void Storage::close(Vector<Section>& tempSections) const
{
    if (tempSections.size() == 0) { // ако няма нищо за изтриване
        std::cerr << "File is already closed or the opened file is empty!" << std::endl;
        return;
    }
    tempSections.clear();
    std::cout << "File closed!" << std::endl;
    std::cout << std::endl;
}

void Storage::save(const char* dir, Vector<Section>& tempSections) const
{
    int n = tempSections.size();

    std::ofstream oFile(dir, std::ios::trunc);
    if (!oFile) {
        std::cerr << "Failed to open!" << std::endl;
        std::cout << std::endl;
        return;
    }
    for (int i = 0; i < n; i++) {
        if (tempSections[i].getShelves().size() == 0) tempSections.removeAtIndex(i);
    }
    oFile << n << std::endl;
    for (int i = 0; i < n; i++) { // запазва данните за склада в текущо отворения файл
        tempSections[i].save(oFile);
        oFile << std::endl;
    }
    oFile.close();
    std::cout << "Changes saved successfully!" << std::endl;
    std::cout << std::endl;
}

void Storage::saveAs(const char* newDir, Vector<Section>& tempSections) const
{ // логовете ще се пазят също в logs.txt
    int n = tempSections.size();

    std::ofstream oFile(newDir, std::ios::trunc);
    if (!oFile) {
        std::cerr << "Failed to open!" << std::endl;
        std::cout << std::endl;
        return;
    }
    for (int i = 0; i < n; i++) {
        if (tempSections[i].getShelves().size() == 0) tempSections.removeAtIndex(i);
    }
    oFile << n << std::endl;
    for (int i = 0; i < n; i++) { // zapazva dannite za sklada v noviya fail
        tempSections[i].save(oFile);
        oFile << std::endl;
    }
    oFile.close();
    std::cout << "Changes saved successfully in " << newDir << "!" << std::endl;
    std::cout << std::endl;
}

void Storage::help() const
{
    std::cout << "The following commands are supported: " << std::endl;
    std::cout << "open <file>           opens <file>" << std::endl;
    std::cout << "close                 closes currently opened file" << std::endl;
    std::cout << "save                  saves updates in currently opened file" << std::endl;
    std::cout << "saveAs <file>         saves updates in <file>" << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;
    std::cout << "display_info              prints info about the available products in storage" << std::endl;
    std::cout << "add                       adds a new product to storage" << std::endl;
    std::cout << "remove                    removes a product from storage" << std::endl;
    std::cout << "update_log <from> <to>    outputs a reference to all updates in the period <from> - <to> (dates)" << std::endl;
    std::cout << "cleanUp                   cleans up the storage from all expired products" << std::endl;
    std::cout << "exit                      exits the program" << std::endl;
    std::cout << std::endl;
}

void Storage::fillShelves(int quantity, const Product& tempProduct, Vector<Shelf>& tempShelves)
{
    // създава и запълва quantity на брой рафтове, кати ги добавя в tempShelves
    for (int j = 0; j < quantity; j++) {
        Shelf tempShelf;
        Product copyOfTempProduct(tempProduct.getProductName(), tempProduct.getExpireDate(), tempProduct.getEntryDate(), tempProduct.getManufacturerName(), 50, tempProduct.getDescription());
        tempShelf.productOnShelf = copyOfTempProduct;
        tempShelf.entryDates.add(tempProduct.getEntryDate());
        tempShelf.productsForEveryDate.add(50);

        tempShelves.add(tempShelf);
    }
}

void Storage::addAndFillNewSections(int numOfNewSections, const Product& tempProduct, Vector<Section>& tempSections, const Date& date)
{
    // добавя и запълва нови секции с дадения продукт, като ги добавя в tempSections
    numOfNewSections = tempProduct.getQuantity() / 2500 + 1;
    for (int i = 0; i < numOfNewSections - 1; i++)
    { // пълнят се цели секции (без последната)
        Vector<Shelf> tempShelves;
        fillShelves(50, tempProduct, tempShelves);

        MyString nameOfSection = tempProduct.getProductName();
        Section newSection(nameOfSection, tempShelves);
        tempSections.add(newSection);

        MyString message, op, numOfSection, filled;
        // създава се съобщение за справка за добавяне
        op = "operation: add | Section: ";
        numOfSection.to_string(tempSections.size());
        filled = " | filled with ";
        message += op;
        message += numOfSection;
        message += filled;
        message += tempProduct.getProductName();
        Log tempLog(date, message);
        logs.add(tempLog);
    }

    int amountForNewSection = tempProduct.getQuantity() % 2500;
    int brOfShelves = amountForNewSection / 50;

    Vector<Shelf> tempShelves;
    fillShelves(amountForNewSection / 50, tempProduct, tempShelves);
    if (brOfShelves > 0) {
        MyString message, op, numOfSection, brOfShelvesStr, sh, prName, with;
        // създава се съобщение за справка за добавяне
        op = "operation: add | Section: ";
        numOfSection.to_string(tempSections.size());
        sh = " | number of shelves filled: ";
        brOfShelvesStr.to_string(brOfShelves);
        with = " | with ";
        prName = tempProduct.getProductName();
        message += op;
        message += numOfSection;
        message += sh;
        message += brOfShelvesStr;
        message += with;
        message += prName;
        Log tempLog(date, message);
        logs.add(tempLog);
    }
    Shelf tempShelf;
    Product copyOfTempProduct(tempProduct.getProductName(), tempProduct.getExpireDate(), tempProduct.getEntryDate(), tempProduct.getManufacturerName(), amountForNewSection % 50, tempProduct.getDescription());
    tempShelf.productOnShelf = copyOfTempProduct;
    tempShelf.entryDates.add(tempProduct.getEntryDate());
    tempShelf.productsForEveryDate.add(amountForNewSection % 50);

    tempShelves.add(tempShelf);

    MyString nameOfSection = tempProduct.getProductName();
    Section newSection(nameOfSection, tempShelves);
    tempSections.add(newSection);
    MyString message, op, numOfSection, numOfShelf, sh, amount_, amountStr, nameOfPr, productStr;
    // създава се съобщение за справка за добавяне
    op = "operation: add | Section: ";
    numOfSection.to_string(tempSections.size() - 1);
    sh = " | Shelf: ";
    numOfShelf.to_string(tempSections[tempSections.size() - 1].getShelves().size());
    productStr = " | product: ";
    nameOfPr = tempProduct.getProductName();
    amountStr = " | amount: ";
    amount_.to_string(amountForNewSection % 50);
    message += op;
    message += numOfSection;
    message += sh;
    message += numOfShelf;
    message += productStr;
    message += nameOfPr;
    message += amountStr;
    message += amount_;
    Log tempLog(date, message);
    logs.add(tempLog);
}

Date Storage::createCurrDate() const
{
    time_t t = time(NULL);
    tm* timePtr = localtime(&t);
    int year = 1900 + timePtr->tm_year;
    int	intMonth = 1 + timePtr->tm_mon;
    int	intDay = timePtr->tm_mday;
    char month[3];
    char day[3];
    if (intMonth < 10) {
        month[0] = '0';
    }
    else {
        month[0] = '1';
    }
    month[1] = intMonth % 10 + '0';
    month[2] = '\0';
    if (intDay < 10) {
        day[0] = '0';
    }
    else {
        day[0] = intDay / 10 + '0';
    }
    day[1] = intDay % 10 + '0';
    day[2] = '\0';
    Date currDate(year, month, day);
    return currDate;
}
