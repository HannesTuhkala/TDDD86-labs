// This is the .h file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header and replace it with your own

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
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

	~Boggle();
	
	void shuffleBoard();

	void insertCustomCubes(std::string* sides);

	std::string boardToString() const;

private:
	Board* board;
};

#endif
