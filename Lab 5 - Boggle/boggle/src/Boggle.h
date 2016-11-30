/*
 * This file is part of an implementation of the Boggle game, by
 * Malcolm Vigren (malvi108) and Hannes Tuhkala (hantu447).
 */

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include <vector>
#include "grid.h"
#include "strlib.h"
#include "lexicon.h"

/*
 * Class representing a cube on the board.
 */
class Cube {
	public:
	Cube();
	/*
	Constructs a Cube with the sides of the given string
	 */
	Cube(std::string sides);
	/*
	Returns the character of the side that is up.
	*/
	char sideUp() const;
	/*
	Selects a random side on the cube to be up.
	*/
	void shuffle();
	/*
	Sets a custom index to be the side facing up.
	*/
	void setSideUp(const unsigned int index);
	/*
	Sets visit status.
	*/
	void setVisited(const bool aFlag);
	/*
	Returns visit status
	*/
	bool isVisited() const;

	private:
	/*
	The characters on each side.
	*/
	std::string sides;
	/*
	The index of the side that is up.
	*/
	int sideUpIndex;
	/*
	Whether cube has been visited by backtracking algorithm. Default is false.
	*/
	bool visited;
	/*
	The number of sides.
	*/
	static const int SIDES = 6;
	
};


/*
 * Class representing the grid of cubes in the Boggle object
 */
class Board {
	public:
	/*
	Constructs a board.
	*/
	Board();
	/*
	Changes the sides of the cubes. Parameter sides must be 16 strings of 6
	characters each.
	*/
	void setCubeSides(const std::vector<std::string>& sides);
	/*
	Sets the cube sides to the default sides.
	*/
	void setDefault();
	/*
	Gets a string representation of the board.
	*/
	std::string toString() const;
	/*
	 * Marks or unmarks a cube as visited in backtracking algorithm.
	 */
	void setVisited(const int row, const int col, const bool aFlag);

	bool isVisited(const int row, const int col) const;
	/*
	 * Returns the up-facing cube side at given index.
	 */
	char cubeSideAt(const unsigned int row, const unsigned int col) const;
	/*
	 * Gets the indices of all neighbors to the given index, and
     * puts them in the given neighbors-vector.
	*/
	void getNeighbors(const int row, const int col, 
            std::vector<std::pair<int, int>>& neighbors) const;
	/*
	 * Gets possible starting points for backtracking algorithm.
     * Puts them in the given vector of
	 * indices where the given char is found.
	 */
	void getPossibleStartingPoints(const char c,
            std::vector<std::pair<int,int>>& startingPoints) const;
	
	/*
	 * Gets indices for ALL of the board's cubes and puts them in
     * the given vector.
	 */
	void getAllStartingPoints(
            std::vector<std::pair<int,int>>& startingPoints) const;

	static const int BOARD_SIZE = 4;

	private:
	/*
	Checks whether the char given is a neighbor to the given index, or if it is
	equal to the char of the given index.
	*/
	bool isNeighbor(const int row, const int col, const char c) const;
	/*
	Shuffles the board.
	*/
	void shuffleBoard();
	/*
	The cubes.
	*/
	Grid<Cube> cubes;

};


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
