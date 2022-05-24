#pragma once
#include <iostream>
#include <list>
#include <cstring>
using namespace std;
//seperate chaining using a linked list
//Hashtable to implement 905, Jimmy
class HashTable {
private:
	static const int hashGroups = 10;
	list<pair<int, string>> table[hashGroups]; // List 1, Index 0, List 2, Index 1.... List 10, Index 9
public:
	bool isEmpty() const;
	int hashFunction(int key);
	void insertItem(int key, string value);
	void removeItem(int key);
	string searchTable(int key);
	void printTable();
};