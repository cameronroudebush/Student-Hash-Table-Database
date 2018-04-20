#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <array>
#include <algorithm>
#include "Slot.h"
#include "Student.h"
#define MAXHASH 1000

using namespace std;

/*This class is used as the main hash table. Uses class T so you can change up what type of values it holds.*/
template <class T> class HashTable {
private:
	float itemCount = 0; //Keeps track of the items to see if its full and for usage in alpha
	int perm[MAXHASH]; //Creates a permutation array for the random probing

	/*Pulled from https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key */
	unsigned int hash(unsigned int x) {
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = (x >> 16) ^ x;
		return x % MAXHASH;
	}

public:
	Slot<T> arr[MAXHASH]; //This is where all of the values and key pairs are stored

	/*Default constructor that fills the permutation array*/
	HashTable() {
		for (int i = 0; i < MAXHASH; i++) {
			perm[i] = i;
		}
		random_shuffle(&perm[0], &perm[MAXHASH]); //calls the random algorithm to randomize whats in the array
	}

	/*Inserts a key value pair and keeps track of collisions. Returns if its sucessful or not.*/
	bool insert(int key, T value, int& collisions) {
		int spot = hash(key); //hashes the key for a spot on the array
		int inserted = 0, temp = 0;
		if (itemCount == 1000) { //if its full we got a problem
			return false;
		}
		while (!inserted) { //loop until you find where to put it
			if (arr[spot].isEmpty() || arr[spot].isTombstone()) { //if the slot type is empty or dead (practically empty) you're good put it there
				arr[spot] = Slot<T>(key, value); //Creates a new slot to put there
				itemCount++; //increase the total items of the array
				return true;
			}
			else if (arr[spot].isNormal()) {
				if (arr[spot].getKey() == key) { //If the slot is full and the keys are the same then we can't add it
					return false;
				}
				else { //random probing
					collisions++; //increases collisions
					spot = (spot + perm[temp]) % MAXHASH; //this uses the permutation array for the random probing and mods it to loop around
					temp++; //Adds one to the slot of permutations incase we have to keep looking
				}
			}
		}
		return false;
	}

	/*This removes something from the table with a given key. Returns if its sucessful or not.*/
	bool remove(int key) {
		int spot = hash(key); //Gets a spot from the hash of the key
		int removed = 0, temp = 0;
		while (!removed) {
			if (arr[spot].getKey() == key) { //If you found it then great job! Get rid of it!
				arr[spot] = Slot<T>(); //Replace the spot with an empty slot
				arr[spot].kill(); //Call the kill function to replace the value type with a tombstone
				itemCount--; //Remove one from total count
				return true;
			}
			if (arr[spot].isTombstone() || arr[spot].isEmpty()) { //If the spot it finds is empty or a tombstone then that key doesn't exist
				return false;
			}
			if (arr[spot].isNormal()) { //If it does exist then we need to random probe
				if (temp == 1000) { //If it loops around 1000 times and doesn't find it then it doesn't exist
					return false;
				}
				spot = (spot + perm[temp]) % MAXHASH; //this uses the permutation array for the random probing and mods it to loop around
				temp++; //Adds one to the slot of permutations incase we have to keep looking
			}
		}
		return false;
	}

	/*Locates the given key and sets it equal to a value to be able to return it. Returns if its sucessful or not.*/
	bool find(int key, T& value) {
		int spot = hash(key); //Gets a spot from the hash of the key
		int found = 0, temp = 0;
		while (!found) {
			if (arr[spot].getKey() == key) { //If the key is found then we are good and set it equal to the value
				value = arr[spot].getValue();
				return true;
			}
			if (arr[spot].isTombstone() || arr[spot].isEmpty()) { //If the spot we end up in is empty or is a tombstone then we have a problem
				return false;
			}
			if (arr[spot].isNormal()) {
				if (temp == 1000) { //If we have itterated 1000 times then its not there
					return false;
				}
				spot = (spot + perm[temp]) % MAXHASH; //this uses the permutation array for the random probing and mods it to loop around
				temp++; //Adds one to the slot of permutations incase we have to keep looking
			}
		}
		return false;
	}

	/*Returns the current loading factor*/
	float alpha() {
		float returner = itemCount / MAXHASH; //sets it to a float because we are going to want some decimal
		return returner;

	}

	/*Overloads the << operator. Returns what we want to print.*/
	friend ostream& operator<<(ostream& os, const HashTable& me) {
		for (int i = 0; i < MAXHASH; i++) { //itterate over the table to print stuff out
			if (me.arr[i].isNormal()) { //As long as something is there we are good to print it out
				os << "Slot: " << i << " Key: " << me.arr[i].getKey(); //Prints out the basic info of what the slot and key is for the given table value
				os << me.arr[i].getValue(); //Calls the value overloaded print. This is used to keep things generic.
			}
		}
		return os;
	}
};
