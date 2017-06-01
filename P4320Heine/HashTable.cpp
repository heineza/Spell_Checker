// Zach Heine
// Member functions that define the functionality for 
// the hash table
// Restrictions: none

#include "HashTable.h"

#ifndef _HASH_TABLE_CPP_
#define _HASH_TABLE_CPP_

// Determine whether a value is contained in the hash table
// at the bucket location specified by the hash function
template<typename HashedVal>
bool HashTable<HashedVal>::contains(const HashedVal &htVal) const
{
	auto & list = ht[hashFnctn(htVal)];
	return find(begin(list), end(list), htVal) != end(list);
}

// Empty and Clear all buckets in the hash table
template<typename HashedVal>
void HashTable<HashedVal>::makeEmpty()
{
	for (auto &list : HashTable)
		list.clear();
}

// Insert a value into the hash table based on the location
// given by the hash function
template<typename HashedVal>
bool HashTable<HashedVal>::insert(const HashedVal &htVal)
{
	auto &list = ht[hashFnctn(htVal)];
	if (find(begin(list), end(list), htVal) != end(list))
		return false;
	list.push_back(htVal);

	return true;
}

// Remove a particular value from the hash table based on its
// location provided by the hash function.
template<typename HashedVal>
bool HashTable<HashedVal>::remove(const HashedVal &htVal)
{
	auto &list = ht[hashFnctn(htVal)];
	auto itr = find(begin(list), end(list), htVal) != end(list);

	if (itr == end(list))
		return false;

	list.erase(itr);
	--currSize;
	return true;
}

// Call the hash class and mod it based on the size of the hash table
template<typename HashedVal>
size_t HashTable<HashedVal>::hashFnctn(const HashedVal &htVal) const
{
	static hash<HashedVal> hf;
	return hf(htVal) % ht.size();
}

// Function used to test my code to see if it was working properly and to determine
// the difference between the maximum list size and the minimum.

/*
template<typename HashedVal>
void HashTable<HashedVal>::printHtToFile(fstream &fout)
{
	int minBucketSize = INT_MAX;
	int maxBucketSize = INT_MIN;
	int avgBucketSize = 0;
	int currBucketSize = 0;
	int totalBucketSize = 0;
	
	fout << "Bucket Sizes" << endl;
	fout << "------------" << endl;
	for (size_t i = 0; i < ht.size(); i++)
	{
		currBucketSize = ht[i].size();
		fout << "List " << i << "'s Size: " << currBucketSize << endl;
		if (currBucketSize < minBucketSize)
			minBucketSize = currBucketSize;
		else if (currBucketSize > maxBucketSize)
			maxBucketSize = currBucketSize;
		totalBucketSize += currBucketSize;
	}
	
	fout << endl;
	avgBucketSize = totalBucketSize / numBuckets;
	fout << "Min Bucket Size = " << minBucketSize << endl;
	fout << "Max Bucket Size = " << maxBucketSize << endl;
	fout << "Avg Bucket Size = " << avgBucketSize << endl;
	fout << endl;

	fout << "Contents of each bucket in the hash table" << endl;
	fout << "-----------------------------------------" << endl;
	for (size_t i = 0; i < ht.size(); i++)
	{
		fout << "List " << i << "'s contents: ";
		for (list<HashedVal>::iterator iter = ht[i].begin(); iter != ht[i].end(); iter++)
		{
			fout << *iter << " ";
		}
		fout << endl;
	}
}
*/

#endif