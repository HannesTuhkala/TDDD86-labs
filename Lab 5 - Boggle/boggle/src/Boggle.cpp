// This is the .cpp file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"

bool alreadyExists(const vector<string>& words, const string& word);

Boggle::Boggle() {
	dictionary = Lexicon(DICTIONARY_FILE);
	userScore = 0;
	computerScore = 0;
}

void Boggle::reset() {
	userScore = 0;
	computerScore = 0;
	userWords.clear();
	computerWords.clear();
}

void Boggle::addUserWord(const string& word) {
	userWords.push_back(word);
	userScore += word.size() - MIN_WORD_LENGTH + 1;
}

void Boggle::setDefaultBoard() {
	board = Board();
	board.setDefault();
}

void Boggle::insertCustomCubes(const vector<string>& sides) {
	board = Board();
	board.setCubeSides(sides);
}

std::string Boggle::boardToString() const {
	return board.toString();
}

bool Boggle::isValidWord(const string word) {
	char c = word.front();
	vector<pair<int,int>> startingPoints = board.getPossibleStartingPoints(c);
	for (pair<int,int> index : startingPoints) {
		if (checkValidWordHelp(word, index)) return true;
	}
	return false;
}

bool Boggle::isValidEnglishWord(const string& word) const {
	return dictionary.contains(word);
}

bool Boggle::isCorrectFormat(const string& word) const {
	return isAlpha(word) && word.size() >= MIN_WORD_LENGTH;
}

vector<string> Boggle::getAllRemainingWords() {
	vector<string> foundWords;
	//since the backtracking algorithm needs more parameters for the recursion
	//to work, a help function is made to start at every character in the board.
	vector<pair<int,int>> startingPoints = board.getAllStartingPoints();
	for (pair<int,int> startingPoint : startingPoints) {
		string startingWord = "";
		startingWord += board.cubeSideAt(startingPoint.first, startingPoint.second);
		getAllRemainingWordsHelp(startingWord, startingPoint, foundWords);
	}
	return foundWords;
}

void Boggle::getAllRemainingWordsHelp(const string& currentWord,
									const pair<int,int>& currentIndex,
									vector<string>& foundWords) {
	//if there are words in the dictionary that contain the current word...
	if (dictionary.containsPrefix(currentWord)) {
		//...and if the current word is a complete word in the dictionary 
		//with more than 4 characters and has not already been added or
		//taken by the user, and if the last character hasn't already been visited...
		int currRow = currentIndex.first;
		int currCol = currentIndex.second;
		if (currentWord.size() >= 4
				&& !alreadyExists(foundWords, currentWord) 
				&& !alreadyExists(userWords, currentWord) 
				&& dictionary.contains(currentWord)
				&& !board.isVisited(currRow, currCol)) {
			//We found a word! Push it to the words.
			foundWords.push_back(currentWord);
			//Since a valid word could be a prefix, we need to continue...
		}
		//Regardless of whether we found a word or the word was only a prefix,
		//we mark the current character as visited.
		board.setVisited(currRow, currCol, true);
		//We gather all neighbors to the current character.
		vector<pair<int,int>> neighbors = board.getNeighbors(currRow, currCol);
		//For every neighboring character...
		for (pair<int,int> neighbor : neighbors) {
			int neighRow = neighbor.first;
			int neighCol = neighbor.second;
			//If the character hasn't already been visited...
			if (!board.isVisited(neighRow, neighCol)) {
				string newWord = currentWord;
				newWord += board.cubeSideAt(neighRow, neighCol);
				//explore all words that could have the currentword + the neighbor
				//character as prefixes. 
				getAllRemainingWordsHelp(newWord, neighbor, foundWords);
			}
		}
		//after we've checked all the words that could be made with the currentword as prefix,
		//we need to unmark the current character as visited.
		board.setVisited(currRow, currCol, false);
	} else {
		//if no words can be made with the current word as prefix, stop.
		return;
	}
}

bool Boggle::checkValidWordHelp(string word, pair<int,int> currIndex) {
	int currRow = currIndex.first;
	int currCol = currIndex.second;
	//If there is only one letter in the word, just check and see if it matches the 
	//character of the current index and if it has been visited.
	if (word.size() == 1) return word[0] == board.cubeSideAt(currRow, currCol) && !board.isVisited(currRow, currCol);

	//Else, if the first letter of the word matches the index of the current character and has not
	//already been checked:
	if (word[0] == board.cubeSideAt(currRow, currCol) && !board.isVisited(currRow, currCol)){
		//We are now checking this character in the board, so mark it as visited.
		board.setVisited(currRow, currCol, true);
		//remove the first character of the word.
		string restWord = word.substr(1, word.size() - 1);
		//get the indices of all neighbors to the current character
		vector<pair<int,int>> neighbors = board.getNeighbors(currRow, currCol);
		//for every neighbor...
		for (pair<int,int> neighbor : neighbors) {
			//check if the substring when taken along the path of the neighbor is valid.
			if (checkValidWordHelp(restWord, neighbor)) {
				//if it is valid, that means the word checked is valid. Unmark the current
				//character as visited and return true.
				board.setVisited(currRow, currCol, false);
				return true;
			}
			//if the word with the neighbor wasnt valid, then check the next neighbor
		}
		//if no neighbor took the word on a valid path,
		//then the word is invalid. Unmark cube as visited and 
		//return false.
		board.setVisited(currRow, currCol, false);
		return false;
		//if the first character doesn't match the current character,
		//or if it has already been visited,
		//the word can't be valid. Return false.
	} else return false;
}

bool Boggle::isAlreadyUsed(const string& word) const {
	return alreadyExists(userWords, word);
}

void Boggle::playComputerTurn() {
	computerWords = getAllRemainingWords();
	for (string word : computerWords) {
		computerScore += word.size() - MIN_WORD_LENGTH + 1;
	}
}

bool alreadyExists(const vector<string>& words, const string& word) {
	for (string w : words) {
		if (word == w) return true;
	}
	return false;
}

bool Boggle::isAlpha(const string& text) const {
	for (char c : text) {
		if (!isalpha(c)) return false;
	}
	return true;
}

string Boggle::wordAt(const unsigned int index, const bool computer) const {
    if (computer) {
        return computerWords[index];
    } else {
        return userWords[index];
    }
}

unsigned int Boggle::userWordsSize() const {
    return userWords.size();
}

unsigned int Boggle::computerWordsSize() const {
    return computerWords.size();
}

unsigned int Boggle::getComputerScore() const {
	return computerScore;
}

unsigned int Boggle::getUserScore() const {
	return userScore;
}
