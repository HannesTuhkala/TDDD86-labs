// This is the .h file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include <vector>
#include "Board.h"
#include "Cube.h"

using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
	/*
	Constructs a Boggle object with a standard Board configuration.
	*/
	Boggle();

	void setDefaultBoard();

	void insertCustomCubes(const vector<string>& sides);

	string boardToString() const;

private:
	Board board;
};

#endif
