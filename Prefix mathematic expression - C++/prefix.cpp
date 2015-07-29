// file prefix.cpp
// @author professor Zander
// @author Duong H Chau
// @version Lab4

// While I have done much of this for you, make sure you understand it all.
// Make sure you understand why the parameters are pass by reference
// in evaluatePrefixHelper and toPostfix.

#include "prefix.h"

//-----------------------------------------------------------------------------
// constructor
// initialize the array to the empty string 
// char arrays are terminated with '\0' so operator<< works properly

Prefix::Prefix() {
   expr[0] = '\0'; 
} 

//-----------------------------------------------------------------------------
// setPrefix
// Set a prefix expression made of single digit operands, operators +,-,*,/
// and no blanks or tabs contained in a file. The expression is valid in
// that each operator has two valid operands.
// @param infile the data file.

void Prefix::setPrefix(ifstream& infile) { 
    infile >> expr;
}

//-----------------------------------------------------------------------------
// evaluatePrefix 
// Evaluate a prefix expr made of single digit operands and operators +,-,*,/
// @return int value of the expression

int Prefix::evaluatePrefix() const {
    if (expr[0] == '\0') 
        return 0;

    int index = -1;                               // to walk through expr
    return evaluatePrefixHelper(index);
}

//-----------------------------------------------------------------------------
// toPostfix, private helper method (recursion method)
// display prefix expression as a string (char array)
// @param index the index of the prefix expression
// @return int value if it is a digit

int Prefix::evaluatePrefixHelper(int& index) const {
    char symbol = expr[++index]; 
	if(isdigit(symbol))     // just return the value of the char if it is a digit
		return symbol - '0';
	switch (symbol){		// makes a specific excecusion for a specific operand		
		case '+': return evaluatePrefixHelper(index)+evaluatePrefixHelper(index);
		case '-': return evaluatePrefixHelper(index)-evaluatePrefixHelper(index);
		case '*': return evaluatePrefixHelper(index)*evaluatePrefixHelper(index);
		case '/': return evaluatePrefixHelper(index)/evaluatePrefixHelper(index);			
	}		
}

//-----------------------------------------------------------------------------
// outputAsPostfix, toPostfix
// Convert prefix expression to postfix and output
// @param out output object

void Prefix::outputAsPostfix(ostream& out) const {
    if (expr[0] == '\0') 
        return;

    int index = -1;                           // to walk through expr
    int count = -1;                           // used to build postfix array
    char postfix[MAXSIZE+1];                  // holds postfix expression
    toPostfix(index, postfix, count);
    postfix[++count] = '\0';
    out << postfix;
}
//-----------------------------------------------------------------------------
// toPostfix, private helper method (recursion method)
// display prefix expression as a string (char array)
// @param index the index of the prefix expression
// @param postfix the char array that stores the expression in postfix order
// @param count the index of the postfix array

void Prefix::toPostfix(int& index, char postfix[], int& count) const {
    char symbol = expr[++index];
    if(isdigit(symbol))                 //just store the character to the array when it's a number
		postfix[++count] = symbol;
	else{                               //stores the next 2 characters before storing the operator
		toPostfix(index,postfix,count); 
		toPostfix(index,postfix,count);
		postfix[++count] = symbol;
	}
}

//-----------------------------------------------------------------------------
// operator<<
// display prefix expression as a string (char array)
// @param output the output object
// @param expression the preference to prefix array
// @return ostream the output
ostream& operator<<(ostream& output, const Prefix& expression) {
    output << expression.expr;
    return output;
}
