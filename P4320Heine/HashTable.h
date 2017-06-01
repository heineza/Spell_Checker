// Zach Heine
// Header File that declares the member functions
// and data members for the hash table
// Restrictions: none

#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<list>

using namespace std;

template<typename HashedVal>
class HashTable
{
public:
	explicit HashTable(int htSize = 1373)
	{
		numBuckets = htSize;
		currSize = 0;
		ht.resize(htSize);

		 for (size_t i = 0; i < ht.size(); i++)
		{
			 ht[i].clear(); 
		}
	};
	bool contains(const HashedVal& htVal) const;

	void makeEmpty();
	bool insert(const HashedVal& htVal);
	bool remove(const HashedVal& htVal);
	void printHtToFile(fstream &fout);
private:
	vector<list<HashedVal>> ht;
	int numBuckets;
	int currSize;

	size_t hashFnctn(const HashedVal &htVal) const;
};

// Class that defines the hash function
template<>
class hash<string>
{
public:
	size_t operator()(const string &key)
	{
		size_t hashVal = 0;
		int len = key.length();
		for (char ch:key)
		{
			hashVal = 29 * hashVal + ch;
		}
		return hashVal;
	}
};

#include "HashTable.cpp"
#endif