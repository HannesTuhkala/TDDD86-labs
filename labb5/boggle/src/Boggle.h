// This is the .h file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include "strlib.h"
#include "Board.h"
#include "Cube.h"
#include "lexicon.h"

using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const unsigned int MIN_WORD_LENGTH = 4;
	/*
	Constructs a Boggle object with a standard Board configuration.
	*/
	Boggle();
	
	void addUserWord(const string& word);
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
	be all alpha characters and atleast 4 chars long.
	*/
	bool isValidWord(const string word);
	/*
	 * Uses backtracking algorithm to find all possible valid English words in the board.
	 */
	vector<string> getAllPossibleWords(const Lexicon& dictionary, const vector<string>& takenWords);

	bool isValidEnglishWord(const string& word) const;

	bool isCorrectFormat(const string& word) const;

	string boardToString() const;
	
	bool isAlpha(const string& text) const;

	bool isAlreadyUsed(const string& word) const;

private:
	Board board;

	Lexicon dictionary;

	vector<string> userWords;

	unsigned int userScore;
	
	bool checkValidWordHelp(string word, pair<int,int> currIndex);

	void getAllPossibleWordsHelp(const Lexicon& dictionary,
									const string& currentWord,
									const pair<int,int>& currentIndex,
									vector<string>& foundWords,
									const vector<string>& takenWords);

//	bool alreadyExists(const vector<string>& words, const string& word) const;
};

#endif
