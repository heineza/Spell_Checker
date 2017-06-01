// Zach Heine
// Spell Checker
// Program that compares a text file against a 
// dictionary in order to determine if the file  
// contains any mispelled words.
// Restrictions: none

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<set>
#include"HashTable.h"
#include"SpellCheck.h"

using namespace std;

int main()
{
	SpellCheck s;
	ifstream infile;
	HashTable<string> dictHt;

	s.readIntoHt(infile, dictHt);
	s.checkWords(dictHt);

	return 0;
}