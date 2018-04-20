#pragma once
#include <string>
#include <iostream>
#include "Slot.h"

/*This class is used for our database example of student records*/
class Student {
public:
	int uid;
	string firstName;
	string lastName;
	string year;

	/*Default constructor*/
	Student() {}

	/*This is a constructor for the sudent class to set all the values.*/
	Student(int newUid, string newFirst, string newLast, string newYear) {
		uid = newUid;
		firstName = newFirst;
		lastName = newLast;
		year = newYear;
	}

	/*This overloads the << operator. This is used so I can keep the overloaded << in hashtable generic so it can be reused for different classes*/
	friend ostream& operator<<(ostream& os, const Student& me) {
		os << " UID: " << me.uid << " First name: " << me.firstName << " Last name: " << me.lastName << " Year: " << me.year << endl; // prints out all of the info
		return os; //Returns it
	}
};