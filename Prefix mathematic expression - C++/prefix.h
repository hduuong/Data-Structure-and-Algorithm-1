// file prefix.h
// @author professor Zander
// @author Duong H Chau
// @version Lab4


#ifndef PREFIX_H
#define PREFIX_H
#include <iostream>
#include <fstream> 
using namespace std;

int const MAXSIZE = 100;                       // maximum size of the char arrays
//-----------------------------------------------------------------------------
// Prefix class :
// A lab that deals with taking mathematical expression in prefix order 
// from a file and evaluate that them, also includes features:
//    -- allows input and output of the whole array
//    -- allows converting prefix to postfix expression
//    -- uses recursion to convert to postfix and evaluate
// Data inclue characters that are digits or operands, for example:
//    -- +23
//    -- -+2/*3-5141
//    -- ++3*-425-+5*+-*211311
//    -- **********22222222222
// Assumptions:
//    -- Format of data is correct (prefix order).
//    -- Data does not exceed the MaxSize
//    -- Char arrays are terminated with '\0', all arrays end with '\0'
//------------------------------------------------------------------------------

class Prefix {
    friend ostream& operator<<(ostream&, const Prefix&);

public:
    Prefix();                                  // default constructor
    void setPrefix(ifstream& infile);          // sets the input to the prefix char array
    int evaluatePrefix() const;                // evaluates the prefix expression
    void outputAsPostfix(ostream&) const;      // converts to postfix order and displays

private:
    char expr[MAXSIZE+1];                      // the expression array 
    int evaluatePrefixHelper(int&) const;      // the recursive method that helps evaluating expression
    void toPostfix(int&, char [], int&) const; // the recursive method that helps displaying the postfix
};

#endif
