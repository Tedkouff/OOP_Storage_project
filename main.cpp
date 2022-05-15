
#include "Storage.h"

using namespace std;

int main()
{
    std::cout << "Welcome to my storage! Please enter a command. If you want to check list with all commands, type 'help'." << std::endl;

    Storage storage;
    Vector<Section> tempSections;
    MyString command, dir;
    bool fileOpened = false;

    cout << "> ";
    while (true)
    {

        cin >> command;
        if (command.size() == 0) continue;
        int brOfIntervals = 0, n = command.size(), numOfWords = 0;
        for (int i = 0; i < n; i++) {
            if (command[i] == ' ') brOfIntervals++;
        }

        Vector<MyString> wordsOfCommand;

        numOfWords = 0;
        int j = 0;
        for (int i = 0; i < n; i++)
        {
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

        if (wordsOfCommand[0] == "close" && numOfWords == 1)
        {
            if (fileOpened) storage.close(tempSections);
            else cout << "You haven't opened a file yet!" << endl;
        }
        else if (wordsOfCommand[0] == "save" && numOfWords == 1) {
            if (fileOpened) storage.save(dir.c_str(), tempSections);
            else cout << "You haven't opened a file yet!" << endl;
        }
        else if (wordsOfCommand[0] == "help" && numOfWords == 1)
            storage.help();
        else if (wordsOfCommand[0] == "exit" && numOfWords == 1) {
            cout << "Exiting program..." << endl;
            return 0;
        }
        else if (wordsOfCommand[0] == "print" && numOfWords == 1) {
            if (fileOpened) storage.displayInformation();
            else cout << "You haven't opened a file yet!" << endl;
        }
        else if (wordsOfCommand[0] == "add" && numOfWords == 1) {
            if (fileOpened) storage.add(tempSections);
            else cout << "You haven't opened a file yet!" << endl;
        }
        else if (wordsOfCommand[0] == "remove" && numOfWords == 1) {
            if (fileOpened) storage.removeProduct(tempSections);
            else cout << "You haven't opened a file yet!" << endl;
        }
        else if (wordsOfCommand[0] == "cleanUp" && numOfWords == 1) {
            if (fileOpened) storage.cleanUp(tempSections);
            else cout << "You haven't opened a file yet!" << endl;
        }
        else if (wordsOfCommand[0] == "open" && numOfWords == 2) {
            dir.clear();
            dir = wordsOfCommand[1];

            fileOpened = true;
            storage.open(dir.c_str(), tempSections);
        }
        else if (wordsOfCommand[0] == "saveAs" && numOfWords == 2) {
            if (fileOpened) storage.saveAs(wordsOfCommand[1].c_str(), tempSections);
            else cout << "You haven't opened a file yet!" << endl;
        }
        else if (wordsOfCommand[0] == "update_log" && numOfWords == 3) {
            if (fileOpened) {
                storage.printLogs(wordsOfCommand[1].c_str(), wordsOfCommand[2].c_str());
            }
            else cout << "You haven't opened a file yet!" << endl;
        }
        else cout << "That command does not exist! Please enter a valid one." << endl;

        command.clear();
        cout << "> ";
    }

    return 0;
}
