
#include "Storage.h"

using namespace std;

int main()
{
    std::cout << "Welcome to my storage! Please enter a command. If you want to check list with all commands, type 'help'." << std::endl;

    Storage storage;
    Vector<Section> tempSections;
    MyString command;
    char* dir = new(nothrow) char[1];
    if(dir == nullptr){
        throw ("No memory for dir!(main.cpp)");
    }
    bool fileOpened = false;

    cout << "> ";
    while (true)
    {
        cin >> command;
        if (command.getSize() == 0) continue;
        int brOfIntervals = 0, n = command.getSize(), numOfWords = 0;
        for (int i = 0; i < n; i++) {
            if (command[i] == ' ') brOfIntervals++;
        }
        char** wordsOfCommand = new(nothrow) char* [brOfIntervals + 1]; // думите на командата
        if (wordsOfCommand == nullptr) {
            delete[] dir;
            throw ("No memory for wordOfCommand!(main.cpp)");
        }
        int sizeOfWord = 0;
        for (int i = 0; i <= n; i++) {  // заделяме памет за думите на командата
            sizeOfWord++;
            if (command[i] == ' ' || command[i] == '\0') {
                wordsOfCommand[numOfWords] = new(nothrow) char[sizeOfWord];
                if (wordsOfCommand[numOfWords] == nullptr) {
                    delete[] dir;
                    for (int j = 0; j < numOfWords; j++) {
                        delete[] wordsOfCommand[j];
                    }
                    delete[] wordsOfCommand;
                    throw ("No memory for wordsOfCommand!(main.cpp)");
                }
                sizeOfWord = 0;
                numOfWords++;
            }
        }
        numOfWords = 0;
        int j = 0;
        for (int i = 0; i < n; i++) { // инициализираме думите на командата
            if (command[i] == ' ') {
                wordsOfCommand[numOfWords][j] = '\0';
                j = 0;
                i++;
                numOfWords++;
            }
            wordsOfCommand[numOfWords][j] = command[i];
            j++;
        }
        wordsOfCommand[numOfWords][j] = '\0';
        numOfWords++;

        // проверява коя е командата
        if (strcmp(wordsOfCommand[0], "close") == 0 && numOfWords == 1) {
            if (fileOpened) storage.close(tempSections);
            else cout << "You haven't opened a file yet!" << endl;
        }
        else if (strcmp(wordsOfCommand[0], "save") == 0 && numOfWords == 1) {
            if (fileOpened) storage.save(dir, tempSections);
            else cout << "You haven't opened a file yet!" << endl;
        }
        else if (strcmp(wordsOfCommand[0], "help") == 0 && numOfWords == 1) storage.help();
        else if (strcmp(wordsOfCommand[0], "exit") == 0 && numOfWords == 1) {
            cout << "Exiting program..." << endl;
            return 0;
        }
        else if (strcmp(wordsOfCommand[0], "display_info") == 0 && numOfWords == 1) {
            if (fileOpened) storage.displayInformation();
            else cout << "You haven't opened a file yet!" << endl;
        }
        else if (strcmp(wordsOfCommand[0], "add") == 0 && numOfWords == 1) {
            if (fileOpened) storage.add(tempSections);
            else cout << "You haven't opened a file yet!" << endl;
        }
        else if (strcmp(wordsOfCommand[0], "remove") == 0 && numOfWords == 1) {
            if (fileOpened) storage.removeProduct(tempSections);
            else cout << "You haven't opened a file yet!" << endl;
        }
        else if (strcmp(wordsOfCommand[0], "clean") == 0 && numOfWords == 1) {
            if (fileOpened) storage.cleanUp(tempSections);
            else cout << "You haven't opened a file yet!" << endl;
        }
        else if (strcmp(wordsOfCommand[0], "open") == 0 && numOfWords == 2) {
            delete[] dir;
            int l = strlen(wordsOfCommand[1]);
            dir = new(nothrow) char[l + 1];
            if (dir == nullptr) {
                for (int j = 0; j < numOfWords; j++) {
                    delete[] wordsOfCommand[j];
                }
                delete[] wordsOfCommand;
                throw ("No memory for dir!(main.cpp)");
            }
            for (int i = 0; i < l; i++) {
                dir[i] = wordsOfCommand[1][i];
            }
            dir[l] = '\0';
            fileOpened = true;
            storage.open(dir, tempSections);
        }
        else if (strcmp(wordsOfCommand[0], "saveAs") == 0 && numOfWords == 2) {
            if (fileOpened) storage.saveAs(wordsOfCommand[1], tempSections);
            else cout << "You haven't opened a file yet!" << endl;
        }
        else if (strcmp(wordsOfCommand[0], "update_log") == 0 && numOfWords == 3) {
            if (fileOpened) storage.printLogs(wordsOfCommand[1], wordsOfCommand[2]);
            else cout << "You haven't opened a file yet!" << endl;
        }
        else cout << "That command does not exist! Please enter a valid one." << endl;

        for (int i = 0; i < numOfWords; i++) {
            delete[] wordsOfCommand[i];
        }
        delete[] wordsOfCommand;
        command.clear();
        cout << "> ";
    }
    delete[] dir;

    return 0;
}
