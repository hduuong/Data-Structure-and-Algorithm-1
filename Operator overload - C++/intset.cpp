// file intset.cpp
// Member function definitions for class IntSet
//
//@author Duong H Chau
//@version lab2

#include "intset.h"

//-----------------------------Constructor---------------------------------------
//a constructor that takes in a maximum parameter of 5.
//this sets value to private data ( size, largest, bool[]).
//parameters that are negative will not be showned in the array.
//@param a, b, c, d, e an integer to put in to the array.
IntSet::IntSet(int a, int b, int c, int d, int e){
	size = 0;
	largest = 0;
	int listValue[MAXINPUT] = {a,b,c,d,e};
	for(int i = 0; i < MAXINPUT; i++){
		if(listValue[i] > 0){
			if(listValue[i] > largest) largest = listValue[i];
		}
	}
	theSet = new bool[largest + 1];
	for(int i = 0; i <= largest; i++){
		theSet[i] = false;
	}
	for(int i = 0; i < MAXINPUT; i++){
		if(listValue[i] > 0 && !theSet[listValue[i]]){
			theSet[listValue[i]] = true;
			size ++;
		}
	}
}

//-----------------------------Copy---------------------------------------
//a copy contructor that contruct a IntSet object that has the same values
//that the object in parameter has.
//@param initual the IntSet object that being copy.
IntSet::IntSet(const IntSet& initual){
	largest = initual.largest;
	size = initual.size;
	theSet = new bool[largest + 1];
	for(int i = 0; i <= largest; i++){
		theSet[i] = initual.theSet[i];
	}
}

//-----------------------------Detructor---------------------------------------
//a detructor that sets all values to NULL values and delete object that is garbage
IntSet::~IntSet(){
	size = 0;
	largest = 0;
	delete [] theSet;
	theSet = NULL;
}
//----------------------------- operator>> ---------------------------------------
//to input an entire set
//stops as the input == -1, and ignores inputs < -1
//@param input the user's input
//@param initual the object that gets to add the new input
//@return the input
istream& operator>>(istream& input, IntSet& initual){
	int newInt;
	input >> newInt;
	while(newInt != -1){
		if(newInt >= 0){
			initual.insert(newInt);
		}
		input >> newInt;
	}
	return input;
}
//----------------------------- operator<< ---------------------------------------
//displays the set containing the integers
//examples: { 1, 2, 3}    for empty set: {}
//@param output the output
//@param initual the object that needed to be print out
//@return the output
ostream& operator<<(ostream& output, const IntSet& initual){
	output << "{";
	for(int i = 0; i <= initual.largest; i++){
		if(initual.theSet[i]){
			output << " " << i;
		}
	}
	output << "}";
	return output;
}
//----------------------------- operator+ ---------------------------------------
//compute and return the union of two sets
//@param right the second set
//@return a IntSet object that contains the value of the union of 2 sets
IntSet IntSet::operator+(const IntSet &right) const{
	IntSet newSet(*this);
	for(int i = 0; i <= right.largest; i++){
		if(right.theSet[i])
			newSet.insert(i);
	}
	return newSet;
}
//----------------------------- operator- ---------------------------------------
//compute and return the difference of set1 to set2
//@param right the second set
//@return a IntSet object that contains the value of the difference
IntSet IntSet::operator-(const IntSet &right) const{
	IntSet newSet1(*this);
	for(int i = 0; i <= right.largest && i <= largest; i++){
		if(theSet[i] && right.theSet[i]){
			newSet1.remove(i);
		}
	}
	return newSet1;
}
//----------------------------- operator* ---------------------------------------
//compute and return the intersections of two sets
//@param right the second set
//@return a IntSet object that contains the value of the intersections
IntSet IntSet::operator*(const IntSet &right) const{
	IntSet newSet;
	for(int i = 0; i <= largest; i++)
		if(right.theSet[i] && theSet[i])
			newSet.insert(i);
	return newSet;
}
//----------------------------- operator= ---------------------------------------
//assigns one set to another
//@param right the set that is used to assign value to another set
//@return the reference to the new set that just get assigned
IntSet& IntSet::operator=(const IntSet& right){
	if(&right != this){
		delete [] theSet;
		size = right.size;
		largest = right.largest;
		theSet = new bool[largest + 1];
		for(int i = 0; i <= largest; i++){
			theSet[i] = right.theSet[i];
		}
	}
	return *this;
}

//----------------------------- operator== ---------------------------------------
//checks if 2 sets are equal to each other
//@param right the second set
//@return true if the 2 sets equals, false if not
bool IntSet::operator==(const IntSet& right) const{
	if(size != right.size) return false;
	if(largest != right.largest) return false;
	for(int i = 0; i <= largest; i++){
		if(theSet[i] && !right.theSet[i]) return false;
		if(!theSet[i] && right.theSet[i]) return false;
	}
	return true;
}
//----------------------------- operator!= ---------------------------------------
//checks if 2 sets are not equal to each other
//@param right the second set
//@return true if the 2 sets are not equal, false if are
bool IntSet::operator!=(const IntSet& right) const{
	int count = 0;
	if(size != right.size) return true;
	if(largest != right.largest) return true;
	for(int i = 0; i <= largest; i++){
		if(theSet[i] && !right.theSet[i]) return true;
		if(!theSet[i] && right.theSet[i]) return true;
	}
	return false;
}
//----------------------------- insert --------------------------------------------
//inserts a number in parameter to the set
//@param num the number needed to be inserted to the set
//@return true if the number gets inserted to the set, false otherwise
bool IntSet::insert(int num){
	if(num > 0){
		if(num > largest){
			bool* newSet = new bool[num+ 1];
			int index;
			for(index = 0; index <= largest; index++){
				newSet[index] = theSet[index];
			}
			for( ; index < num; index++){
				newSet[index] = false;
			}
			newSet[num] = true;
			largest = num;
			size++;
			delete [] theSet;
			theSet = newSet;
			newSet = NULL;
			return true;
		}else{
			if(!theSet[num]){
				size++;
				theSet[num] = true;	
				return true;
			}
		}
	}
	return false;
}

//----------------------------- remove --------------------------------------------
//removes a number in parameter from the set
//@param num the number needed to be removed from the set
//@return true if the number in the set gets removed, false otherwise
bool IntSet::remove(int num){
	if(num > largest || num < 0 || !theSet[num])
		return false;
	if(theSet[num]){
		theSet[num] = false;
		size--;
	}
	if(!theSet[largest]){
		int newLargest = 0;
		for(int i = largest; i >= 0; i--){
			if(theSet[i])
				newLargest = i;
		}
		bool* newSet = new bool[newLargest+1];
		for(int i = 0; i <= newLargest; i++)
			newSet[i] = theSet[i];              
		delete [] theSet;
		largest = newLargest;
		theSet = newSet;
		newSet = NULL;
	}
	return true;
}
//----------------------------- operator+= ---------------------------------------
//this find the union and assign it to the implicit parameter.
//@param right the second set
//@return return the reference to the new calculated object.
IntSet& IntSet::operator+=(const IntSet &right){
	for(int i = 0; i <= right.largest; i++){
		if(right.theSet[i]){
			insert(i);
		}
	}
	return *this;
}
//----------------------------- operator-= ---------------------------------------
//this find the difference and assign it to the implicit parameter.
//@param right the second set
//@return return the reference to the newly calculated object.
IntSet& IntSet::operator-=(const IntSet &right){
	for(int i = 0; i <= largest; i++){
		if(theSet[i] && right.theSet[i]){
			remove(i);
		}
	}
	return *this;
}
//----------------------------- operator*= ---------------------------------------
//this find the intersections and assign it to the implicit parameter.
//@param right the second set
//@return return the reference to the newly calculated object.
IntSet& IntSet::operator*=(const IntSet &right){
	for(int i = 0; i <= largest; i++){
		if(theSet[i] && !right.theSet[i]){
			remove(i);
		}
	}
	return *this;
}
//----------------------------- isInSet ---------------------------------------
//this checks if the object include the value in the parameter.
//@param num, the number that needed to be checked.
//@return true if num is in the set, false otherwise.
bool IntSet::isInSet(int num){
	if(num > largest || num < 0) return false;
	if(theSet[num]) return true;
	return false;
}
//----------------------------- isEmpty ---------------------------------------
//this check if a IntSet object is empty or not
//@return true if the object is empty, false otherwise
bool IntSet::isEmpty(){
	if(size == 0) return true;
	return false;
}