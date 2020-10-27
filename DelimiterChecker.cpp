#include "DelimiterChecker.h"

// default constructor
DelimiterChecker::DelimiterChecker() {
    delimiterStack = new GenStack<char>(64);
    currLineNum = 0;
    currChar = 0;
}

// destructor
DelimiterChecker::~DelimiterChecker() {
    delete delimiterStack;
}

// PUBLIC METHODS

// adds delimiters to stack, returns true if error
bool DelimiterChecker::checkLine(string line) {
    currLineNum++;

    for(char c : line) {
        currChar = c;
        if(isOpenDelimiter(currChar)) {
            delimiterStack->push(currChar);
        } else if(isCloseDelimiter(currChar)) {
            char prevDelimiter;
            try {
                prevDelimiter = delimiterStack->peek();
            } catch(const char *) {
                return true;
            }
            if(isMatchingPair(currChar, prevDelimiter)) {
                delimiterStack->pop();
            } else {
                return true;
            }
        }
    }
    return false;
}

// called at end of file, returns true if stack is not empty
bool DelimiterChecker::checkEndState() {
    return (!delimiterStack->isEmpty());
}

// prints error for close delimiter not matching previous
void DelimiterChecker::printMismatchError() {
    cout << "ERROR: Line " << to_string(currLineNum) << endl;
    if(delimiterStack->isEmpty()) {
        cout << "Unexpected close delimiter \'" << currChar << "\'; no previous open delimiter found\n" << endl;
    } else {
        cout << "Expected \'" << getMatchingPair(delimiterStack->peek()) << "\', found \'" << currChar << "\'\n" << endl;
    }
}

// prints error for end of file and stack is not empty
void DelimiterChecker::printEndOfFileError() {
    cout << "ERROR: Line " << to_string(currLineNum) << endl;
    cout << "Reached end of file, expected \'" << getMatchingPair(delimiterStack->peek()) << "\'\n" << endl;
}

// prints success message when no errors are found
void DelimiterChecker::printSuccess() {
    cout << "Delimiter syntax is correct; no errors detected.\n" << endl;
}

// PRIVATE METHODS

// returns true if char is open delimiter
bool DelimiterChecker::isOpenDelimiter(char c) {
    return ( c == '(' || c == '[' || c == '{' );
}

// returns true if char is close delimiter
bool DelimiterChecker::isCloseDelimiter(char c) {
    return ( c == ')' || c == ']' || c == '}' );
}

// returns true if chars are pair of delimiters
bool DelimiterChecker::isMatchingPair(char open, char close) {
    return (open == getMatchingPair(close));
}

// returns matching delimiter for char
char DelimiterChecker::getMatchingPair(char c) {
    switch(c) {
        case '(':
            return ')';
        case ')':
            return '(';
        case '[':
            return ']';
        case ']':
            return '[';
        case '{':
            return '}';
        case '}':
            return '{';
        default:
            return -1;
    }
}
