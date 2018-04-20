#pragma once
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

// There are three types of slots in a closed hash:
// Normal (full) slots, empty slots, and tombstones
enum SlotType { normalSlot, emptySlot, tombstone };


// Each record holds an integer key and a value of any type
// (hence the need for a template).  The value type must be
// printable using << or this code will fail.  
//
// In this implementation, the value is stored directly in
// the record.  If the value is large, it would be more
// efficient to have the records hold pointers to the values.
// In this case, care would need to be taken to ensure
// that deep copies are made upon assignment, and that
// any values allocated are properly deleted in the Record
// destructor.
template <class T> class Slot {
private:
	int key;
	T value;
	SlotType type;

public:

	// The default constructor produces an empty record.
	// A possibly better way to keep track of tombstones and emtpy
	// records would be to use inheritance, similar to the way we
	// avoided having null pointers in leaf nodes for binary trees.
	Slot()
	{
		key = 0;
		type = emptySlot;
	}

	// This constructor uses an initialization list
	// See "member initialization" at: http://www.cplusplus.com/doc/tutorial/classes/
	Slot(int newkey, T newvalue)
		: key(newkey), value(newvalue)
	{
		type = normalSlot;
	}

	// Convert a record to a tombstone
	void kill() {
		type = tombstone;
	}

	// Get the integer key of a record
	int getKey() const {
		return key;
	}

	// Get the value of a record
	T getValue() const {
		return value;
	}

	// Check if a record is empty
	bool isEmpty() const {
		return(type == emptySlot);
	}

	// Check if a record is a normal record
	bool isNormal() const {
		return(type == normalSlot);
	}

	// Check if a record is a tombstone
	bool isTombstone() const {
		return (type == tombstone);
	}

	// Overload the << operator for printing records
	friend ostream& operator<<(ostream& os, const Slot& me) {
		if (me.isTombstone())
			os << "<<Tombstone>>";
		else if (me.isEmpty())
			os << "<<Empty>>";
		else
			os << "Key: " << me.key << ", Value: " << me.value;
		return os;
	}

	~Slot()
	{
	}
};