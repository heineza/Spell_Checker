// Zach Heine
// Spell Check Header that contains
// the functionality for the spell
// checker
// Restrictions: none

#ifndef _SPELL_CHECK_H_
#define _SPELL_CHECK_H_

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "HashTable.h"

using namespace std;

class SpellCheck{
public:
	ifstream& getWord(ifstream& infile, string& w);
	void readIntoHt(ifstream &infile, HashTable<string> &ht);
	void readIntoSet(ifstream &infile, HashTable<string> ht, set<string> &mispelledWords);
	void checkWords(HashTable<string> ht);
	void outputWords(set<string> mispelledWords);
};

ifstream& SpellCheck::getWord(ifstream& infile, string& w)
{
	char c;
	w = "";		  // clear the string of characters

	while (infile.get(c) && !isalpha(c))
		;		  // do nothing. just ignore c

	// return on end-of-file
	if (infile.eof())
		return infile;

	// record first letter of the word
	w += tolower(c);

	// collect letters and digits
	while (infile.get(c) && (isalpha(c) || isdigit(c)))
		w += tolower(c);

	return infile;
}

// Function that reads from a dictionary file and stores them in buckets
// in a hash table
void SpellCheck::readIntoHt(ifstream &infile, HashTable<string> &ht)
{
	fstream outfile;
	string infileName = "dict.dat";
	string outfileName = "test.txt";
	string currWord = "";

	infile.open(infileName, fstream::in);
	if (infile.fail())
	{
		cerr << "ERROR: Cannot open file! Terminating program...";
		exit(1);
	}

	outfile.open(outfileName, fstream::out);
	if (outfile.fail())
	{
		cerr << "ERROR: Cannot open file! Terminating program...";
		exit(1);
	}

	while (!infile.eof())
	{
		getWord(infile, currWord);
		ht.insert(currWord);
	}
	// Previously used function that tested the quality of the hash function
	//ht.printHtToFile(outfile);
	currWord = "";
	outfile.close();
	infile.close();
}

// Read in from the file and compare the words against the hash table
// If they are not found store them in a set containing the mispelled
// words
void SpellCheck::readIntoSet(ifstream &infile, HashTable<string> ht, set<string> &mispelledWords)
{
	string currWord = "";
	while (!infile.eof())
	{
		getWord(infile, currWord);
		if (ht.contains(currWord) == false)
		{
			mispelledWords.insert(currWord);
		}
	}
}

// Open the file that is to be read into the set and check if 
// it is a valid file then call the function to read the file
// into the set and the function to output the words to the 
// standard output stream.
void SpellCheck::checkWords(HashTable<string> ht)
{
	ifstream infile;
	string infileName = "";
	string currWord = "";
	set<string> mispelledWords;

	cout << "Enter the document name that contains the file to be spell-checked: ";
	cin >> infileName;

	infile.open(infileName, fstream::in);
	if (infile.fail())
	{
		cerr << "ERROR: Cannot open file! Terminating program..." << endl;
		exit(1);
	}

	readIntoSet(infile, ht, mispelledWords);
	outputWords(mispelledWords);
}

// Output the set of mispelled words to the standard output stream.
void SpellCheck::outputWords(set<string> mispelledWords)
{
	if (mispelledWords.size() > 0)
	{
		cout << "Mispelled Words:" << endl;
		cout << endl;
		for (set<string>::iterator iter = mispelledWords.begin(); iter != mispelledWords.end(); iter++)
		{
			cout << *iter << endl;
		}
	}
}

#endif