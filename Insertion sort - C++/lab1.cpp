// ----------------------------------------------------------------------------

// a lab that deals with taking information from a file and sort it as specified
// sorting method: insertion sort
// display the sorted info and the histogram of grade
// Data includes last name, first name, and grade. For example:
// 
// duck donald 50
// mouse mickey 22
// mouse minnie 90
//
// Assumptions:
//    -- Format of data is correct.
//    -- All names are no more in length than MAXLENGTH.
//    -- grades are integer, and in range between LOWGRADE and MAXGRADE.
//    -- Data that has grade out of range will not be included in the lists.
// @author Duong H Chau
// @version Lab1
//------------------------------------------------------------------------------

#include <string.h>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int const MAXSIZE = 100;            // maximum number of records in total
int const MAXLENGTH = 31;           // maximum string length 
int const MAXGRADE = 100;           // highest possible grade
int const LOWGRADE = 0;             // lowest possible grade
int const GROUP = 10;               // group amount
int const HISTOGRAMSIZE = (MAXGRADE-LOWGRADE)/GROUP + 1;    // grouped by GROUP

struct StudentType  {               // information of one student
   int grade;                       // the grade of the student
   char last[MAXLENGTH];            // last name (MAXLENGTH-1 at most)
   char first[MAXLENGTH];           // first name (MAXLENGTH-1 at most)
};

// prototypes go here
bool sortInput(istream&, StudentType [], int&);
void displayList(const StudentType [], const int);
void setHistogram(StudentType [],const int, int []);
void displayHistogram(const int []);
int findAverage(const StudentType [],const int);
//------------------------------- main ----------------------------------------
int main()  {
   StudentType students[MAXSIZE];   // list of MAXSIZE number of students
   int size = 0;                    // total number of students
   int histogram[HISTOGRAMSIZE];    // grades grouped by GROUP
   int average = 0;                 // average exam score, truncated

   // creates file object and opens the data file
   ifstream infile("data1.txt");
   if (!infile)  { 
      cout << "File could not be opened." << endl; 
      return 1;  
   }

   // read and sort input by last then first name
   bool successfulRead = sortInput(infile, students, size);              

   // display list, histogram, and class average 
   if (successfulRead)  {
      displayList(students, size);
	  setHistogram(students, size, histogram);
	  displayHistogram(histogram);
      average = findAverage(students, size);
      cout << endl << "Average grade: " << average << endl << endl;
   }
   return 0;
}

//---------------------------------sortInput-------------------------------------
//a method that takes value from a file, and sort them using insertion sort
//@param infile the file contains data needed to be sorted
//@param theClass[] the array of StudentType
//@param size the size of the array
//@return a bool, true if able to be sorted, false if not.
bool sortInput(istream& infile, StudentType theClass[], int& size){
	StudentType temp;
	infile >> temp.last;
	while( size < MAXSIZE && !infile.eof() ){
		infile >> temp.first >> temp.grade;
		if(temp.grade >= LOWGRADE && temp.grade <= MAXGRADE){
			int idx = size;
			while(idx >= 1){
				if(strcmp(temp.last,theClass[idx-1].last) < 0){
					theClass[idx] = theClass[idx-1];
					idx--;
				}
				else if(strcmp(temp.last,theClass[idx-1].last) == 0
					&& strcmp(temp.first,theClass[idx-1].first) < 0){
						theClass[idx] = theClass[idx-1];
						idx--;
				}
				else
					break;
			}
			theClass[idx] = temp;
			size ++;
		}
		infile >> temp.last;
	}
	return true;
}

//-----------------------------------displayList-------------------------------------
//a method that print/display the list of sorted input
//@param theClass[] the array of StudentType
//@param size the size of the array
void displayList(const StudentType theClass[],const int size){
	cout << "List of names sorted:" << endl;
	for(int i = 0; i < size; i++){
		cout<< " " << theClass[i].grade << "  " << theClass[i].last
			<< " " << theClass[i].first << endl;
	}
}

//----------------------------------findAverage--------------------------------------
//a method that calculate the average grade and return it as an integer
//@param theClass[] the array of StudentType
//@param size the size of the array
//@return the int value of the average grade
int findAverage(const StudentType theClass[],const int size){
	int sum = 0;
	for(int i = 0; i < size; i++){
		sum += theClass[i].grade;
	}
	return sum/size;
}
//-----------------------------------setHistogram------------------------------------
//a void method that set values into the int[] of Histogram
//@param theClass[] the StudentType array
//@param size the constant value of the size of StudentType array
//@param theHistogram[] the Histogram's int array
void setHistogram(StudentType theClass[], const int size, int theHistogram[]){
	for(int i = 0; i < HISTOGRAMSIZE; i++){
		theHistogram[i] = 0;
	}
	for(int i = 0; i < size; i++){
		int index = theClass[i].grade / 10;
		theHistogram[index]++;
	}
}
//-----------------------------------displayHistogram--------------------------------
// a void method that display the Histogram
// @param theHistogram[] the Histogram's int array
void displayHistogram(const int theHistogram[]){
	cout << endl;
	cout << "Histogram of grades:" << endl;
	int from = LOWGRADE;
	int to = LOWGRADE + 9;
	for(int i = 0; i < HISTOGRAMSIZE - 1; i++){
		cout << setw(4) << from << "-->"
			 << setw(4) << to << ": ";
		for(int n = theHistogram[i]; n > 0; n--)
			cout << "*";
		cout << endl;
		from += 10;
		to += 10;
	}
	cout << setw(4) << MAXGRADE << "-->"
		<< setw(4) << MAXGRADE << ": ";
	for(int n = theHistogram[HISTOGRAMSIZE - 1]; n > 0; n--){
		cout << "*";
	}
	cout << endl;
}


