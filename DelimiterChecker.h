#ifndef DELIMITERCHECKER
#define DELIMITERCHECKER

#include "GenStack.h"

/*
    DelimiterChecker implements a GenStack in order to keep track of delimiters.
    - Is passed strings and it stores delimiters in a stack
    - Can return error information through multiple methods
*/
class DelimiterChecker {

    public:
        DelimiterChecker(); // default constructor
        ~DelimiterChecker(); // destructor

        bool checkLine(string line); // adds delimiters to stack, returns true if error
        bool checkEndState(); // called at end of file, returns true if stack is not empty

        void printMismatchError(); // prints error for close delimiter not matching previous
        void printEndOfFileError(); // prints error for end of file and stack is not empty
        void printSuccess(); // prints success message when no errors are found

    private:
        GenStack<char> *delimiterStack; // holds delimiters found from file
        int currLineNum; // keeps track of the current line number in file
        char currChar; // keeps track of current delimiter char being evaluated

        bool isOpenDelimiter(char c); // returns true if char is open delimiter
        bool isCloseDelimiter(char c); // returns true if char is close delimiter
        bool isMatchingPair(char open, char close); // returns true if chars are pair of delimiters
        char getMatchingPair(char c); // returns matching delimiter for char
};

#endif
