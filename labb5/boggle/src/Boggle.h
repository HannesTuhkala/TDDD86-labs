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
#include "lexicon.h"

using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
	/*
	Constructs a Boggle object with a standard Board configuration.
	*/
	Boggle();
	/*
	Sets the board to the default cube sides
	*/
	void setDefaultBoard();
	/*
	Sets the board to custom cube sides.
	*/
	void insertCustomCubes(const vector<string>& sides);
	/*
	Checks if a given word could be made from the board. The given word must
	be all alpha characters and exactly 4 chars long.
	*/
	bool isValidWord(const Lexicon& dict, string word) const;

	string boardToString() const;

private:
	Board board;
};

#endif
