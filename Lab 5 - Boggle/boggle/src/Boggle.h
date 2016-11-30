/*
 * This file is part of an implementation of the Boggle game, by
 * Malcolm Vigren (malvi108) and Hannes Tuhkala (hantu447).
 */

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
	/*
	 * Resets the game, but does not reload the dictionary.
	 */
	void reset();
	/*
	 * Adds a valid user word to the list of user words.
	 */
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
	 * Checks if the given word is contained within the dictionary.
	 */
	bool isValidEnglishWord(const string& word) const;
	/*
	 * Checks whether a word has the correct format for the Boggle-rules.
	 */
	bool isCorrectFormat(const string& word) const;
	/*
	 * Returns a string representation of the board.
	 */
	string boardToString() const;
	/*
	 * Returns whether a string has only alpha-characters.
	 */
	bool isAlpha(const string& text) const;
	/*
	 * Returns whether the word entered has already been entered by the user.
	 */
	bool isAlreadyUsed(const string& word) const;
	/*
	 * Computes the remaining words on the board and saves them in the computerWords-field.
	 * Also computes the computer's score and saves it in the computerScore-field.
	 */
	void playComputerTurn();
	/*
	 * Returns the computerScore-field.
	 */
	unsigned int getComputerScore() const;
	/*
	 * Returns the userScore-field.
	 */
	unsigned int getUserScore() const;
    /*
     * Returns the word at the given index, from the user words
     * (computer = false) or the computer words (computer = true)
     */
    string wordAt(const unsigned int index, const bool computer) const;
    /*
     * Returns the amount of words in the user words list.
     */
    unsigned int userWordsSize() const;
    /*
     * Returns the amount of words in the computer words list.
     */
    unsigned int computerWordsSize() const;

private:

	Board board;

	Lexicon dictionary;

	vector<string> userWords;

	vector<string> computerWords;

	unsigned int userScore;

	unsigned int computerScore;
	/*
	 * Help function for isValidWord().
	 */
	bool checkValidWordHelp(string word, pair<int,int> currIndex);
	/*
	 * Help function for getAllRemainingWords(). Finds all words that have not yet been 
	 * entered by the user and saves them in the given foundWords-variable.
	 */
	void getAllRemainingWordsHelp(const string& currentWord,
								const pair<int,int>& currentIndex,
								vector<string>& foundWords);
	/*
	 * Uses backtracking algorithm to find all possible valid English 
     * words in the board, and puts them in the given foundWords vector.
	 */
	void getAllRemainingWords(vector<string>& foundWords);

};

#endif
