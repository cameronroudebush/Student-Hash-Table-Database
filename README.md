# Student-Hash-Table-Database
Project 4 for my CS 3100 class (Data Structures). This project creates a student database implemented as a Hash Table.
CS 3100 – Data Structures and Algorithms
Project #4 – Hash Table Indexing
Learning Objectives

 - Implement a data structure to meet given specifications
 - Design, implement, and use a closed hash table data structure
 - Perform empirical analysis of algorithm performance
 - Use a hash table as an index to a data store

Overview

Your task for this assignment is to implement a closed hash table data structure, and to use this hash as the index for rapid searching of a database of student records.
The HashTable class

Your hash table should be implemented as an array of MAXHASH objects of class Slot. A Slot contains an integer key (the student's UID), and a value, which can be of any type. The implementaiton of class Slot will be provided for you in the file Slot.h. The value of MAXHASH should initially be #defined to 1000.

Your hash table should accept integer keys, and any type of value. To implement the hash table, you should create a class template called HashTable, implemented inline in the file HashTable.h. Your class should support the following operations (for any class T):
- bool HashTable<T>::insert(int key, T value, int& collisions) – Insert a new key/value pair into the table. Duplicate keys are not allowed. This function should return true if the key/value pair is successfully inserted into the hash table, and false if the pair could not be inserted (for example, due to a duplicate key already found in the table). If the insertion is successful, the number of collisions occuring during the insert operation should be returned in collisions.

- bool HashTable<T>::remove(int key) – If there is a record with the given key in the hash table, it is deleted and the function returns true; otherwise the function returns false.

- bool HashTable<T>::find(int key, T& value) – If a record with the given key is found in the hash table, the function returns true and a copy of the value is returned in value. Otherwise the function returns false.

- float HashTable<T>::alpha() ‐ returns the current loading factor, α, of the hash table.

 - Your hash table should also overload operator<< such that cout << myHashTable prints all the key/value pairs in the table, along with their hash table slot, to cout.

The hash and probe functions

Because this is a closed hash, you will need both a hash function and a probe function. You are free to implement any hash function you like. For example, you may choose to implement some form of the ELFhash, given in Chapter 9 of your textbook, or any other hash function that will work on integer keys. Remember to cite your source if you use code written by anyone other than yourself!

Your hash should use pseudo-random probing to resolve collisions.
Implementing your database

Your hash table should be used as an index for a database of student records. Each student record should contain the student's last name, first name, UID, major, and year (freshman, sophomore, etc.). Student record objects should be stored in the hash table.
Main program

You should use your student database in a main program that allows a user to insert, search, and delete from the database.
Example program operation

    Would you like to (I)nsert or (D)elete a record, or (S)earch for a record, or (Q)uit?
    Enter action:  I
    Inserting a new record.
    Last name:  Doe
    First name:  Jane
    UID: 1234
    Year:  Junior
    Record inserted.

    Would you like to (I)nsert or (D)elete a record, or (S)earch for a record, or (Q)uit?
    Enter action:  S
    Enter UID to search for: 1234
    Searching... record found
    ----------------------------
    Last name:  Doe
    First name:  Jane
    UID: 1234
    Year:  Junior
    ----------------------------

    Would you like to (I)nsert or (D)elete a record, or (S)earch for a record, or (Q)uit?
    Enter action:  S
    Enter UID to search for: 2345
    Searching... record not found

    Would you like to (I)nsert or (D)elete a record, or (S)earch for a record, or (Q)uit?
    Enter action:  Q
    Exiting.

Turn in and Grading
 - The HashTable class should be implemented as an inline class in the file HashTable.h -- 
    it should be implemented as a template to allow any type of value to be stored in the table. 
    You may choose the filenames for all other classes and code. We will test your HashTable.h with our test harness, 
    and then test your complete database using your main program.
 - Please zip your entire project directory into a single file called Project4.zip.

This project is worth 50 points, distributed as follows:
Task 	Points
 - HashTable::insert stores key/value pairs in the hash table using appropriate hashing and collision resolution, and correctly rejects duplicate keys and reports correct collision counts. Insert correctly re-uses space from previously-deleted records. 	5
 - HashTable::find correctly finds records in the hash table using appropriate hashing and collision resolution, and returns either the value associated with the search key or false when the requested key is not present in the hash table. 	5
 - HashTable::remove correctly finds and deletes records from the table, without interfering with subsequent search or insert operations. 	5
 - AVLTree::alpha correctly calculates and returns the load factor of the table. 	5
 - operator<< is correctly overloaded to print the hash table slot, key, and value of all records in the table 	5
 - The hash table avoids excessive primary and secondary clustering 	5
 - Code is well organized, well documented, and properly formatted. Variable names are clear, and readable. Classes are declared and implemented in seperate (.cpp and .h) files. 	5
 - The HashTable is implemented as a template, allowing any type for the record values, and is correctly implemented in separate .h and .cpp files. 	5
 - The main program uses the hashtable as a record store to create a working student database that correctly supports insertion, deletion, and search of student objects. 	10
