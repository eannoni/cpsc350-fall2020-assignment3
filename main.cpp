#include "DelimiterChecker.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char **argv) {

    string fileName = "";
    bool running = true;

    // get command line input
    if(argc != 2) {
        cout << "Invalid command line parameters, please enter a file name." << endl;
        return -1;
    } else {
        fileName = argv[1];
    }

    cout << "\n\n\n}---------------------| Syntax Checker |---------------------{\n" << endl;

    // loops for each file checked
    while(running) {
        ifstream file;
        DelimiterChecker *delimiterChecker = new DelimiterChecker();
        bool errorDetected = false;

        // open file
        file.open(fileName);
        while(!file.is_open()) {
            cout << "Unable to locate file \'" << fileName << "\'. Please input name of a file: ";
            cin >> fileName;
            file.open(fileName);
        }
        cout << "\nChecking file \'" << fileName << "\' for delimiter errors...\n" << endl;

        // iterate through file lines and get delimiter information
        while(!file.eof() && !errorDetected) {
            string currLine;

            // get next line from file
            getline(file, currLine);

            // pass line to delimiterChecker and get bool (true = error, false = no error)
            errorDetected = delimiterChecker->checkLine(currLine);
        }

        // print error/success message
        if(errorDetected) {
            delimiterChecker->printMismatchError();
        } else if(delimiterChecker->checkEndState()) {
            delimiterChecker->printEndOfFileError();
        } else {
            delimiterChecker->printSuccess();
        }

        // prompt if want to try another file
        string userInput;
        cout << "Would you like to test another file? Enter \'yes\' or \'no\': ";
        while(true) {
            cin >> userInput;
            if(userInput == "yes") {
                break;
            } else if (userInput == "no") {
                running = false;
                break;
            }
            cout << "Incorrect input. Please enter \'yes\' or \'no\': ";
        }

        // get new file name
        if(running) {
            cout << "Please input name of a file: ";
            cin >> fileName;
        }

        // clean-up
        file.close();
        delete delimiterChecker;
    }

    cout << "\nExiting program.\n" << endl;
    return 0;
}
