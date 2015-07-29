// file array.h
// Simple class Array (for integers)
// @author Duong H Chau
// @version lab2

#ifndef INTSET_H
#define INTSET_H
#include <iostream>
using namespace std;
//---------------------------------------------------------------------------------
// IntSet class: includes
//   -- size, number of integers in set
//   -- theSet, a bool array
//   -- largest, an element decides the size of the bool array
//   -- MAXINPUT, a static const int that indicate the max number of parameters for constructor
// Features:
//   -- constructs a set of ints through values put in the constructor
//   -- allows user to set inputs for a set as long as it is not -1
//   -- allows output to display the entire list of integer in the format
//                        { 3, 7, 9}
//   -- allows user to find the union, difference, and intersection between 2 sets
//   -- allows user to compare 2 sets
//   -- allows user to checks if the set is empty or not
//   -- allows user to checks if a element is in the set or not
// Assumptions:
//   -- maximum number of parameters for constructor is 5
//   -- negative parameters for constructor and nagative inputs will not be showned
//   -- 
//---------------------------------------------------------------------------------
class IntSet {                           
public:
	IntSet(int = -1, int = -1, int = -1, int = -1, int = -1);
	IntSet(const IntSet &);
	~IntSet();

	IntSet operator+(const IntSet &) const;
	IntSet operator-(const IntSet &) const;
	IntSet operator*(const IntSet &) const;

	IntSet& operator=(const IntSet &);
	IntSet& operator-=(const IntSet &);       
	IntSet& operator*=(const IntSet &);       
	IntSet& operator+=(const IntSet &);       

	bool operator==(const IntSet &) const;      
	bool operator!=(const IntSet &) const;      

	bool isEmpty();
	bool isInSet(int);
	bool insert(int);
	bool remove(int);

	friend ostream& operator<<(ostream&, const IntSet&);
	friend istream& operator>>(istream&, IntSet&);

private:
   int size,largest;
   bool *theSet;
   static int const MAXINPUT = 5;       // the maximum number of parameters that a constructor can have
};

#endif
