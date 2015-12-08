#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "lexicon.h"
#include "bogglemain.h"
#include "strlib.h"
#include "Board.h"
#include "Cube.h"
#include <cctype>

static const int NUM_CUBES = 16;

void clearConsole();
void playOneGame(Boggle& boggle);
void inputCustomSides(Boggle& boggle);
void printWords(vector<string>& words, bool computer);
void updateScore(string& word, unsigned int& score);
vector<string> createSides(string& ans);
void enterWord(Boggle& boggle, vector<string>& words);
void printScore(unsigned int score);
bool randomBoard();
unsigned int countComputerScore(vector<string> words);

/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle& boggle) {
	if (randomBoard()) {
		boggle.setDefaultBoard();
	} else {
		inputCustomSides(boggle);
	}
	vector<string> words;
	unsigned int score = 0;
	cout << "It's your turn!" << endl;
	cout << boggle.boardToString() << endl;
	cin.ignore();
	while (true) {
		printWords(words, false);
		printScore(score);
		enterWord(boggle, words);
		if (temp.empty()) break;
		words.push_back(temp);
		updateScore(temp, score);
		cout << "You found a new word! \"" << temp << "\"" << endl;
	}
	//computer's turn
	cout << "It's my turn!" << endl;
	vector<string> allWords = boggle.getAllPossibleWords(dictionary, words);
	printWords(allWords, true);
	unsigned int computerScore = countComputerScore(allWords);
	cout << "My score: " << computerScore << endl;
	if (computerScore > score) {
		cout << "Ha ha ha, I destroyed you. Better luck next time, puny human!" << endl;
	} else {
		cout << "Wow, we both found the same number of words...how???" << endl;
	}
}

unsigned int countComputerScore(vector<string> words) {
	unsigned int score = 0;
	for (string word : words) {
		updateScore(word, score);
	}
	return score;
}

void updateScore(string& word, unsigned int& score) {
	score += word.size() - 3;
}

void enterWord(Boggle& boggle, vector<string>& words) {
	cout << "Type a word (or press Enter to end your turn): ";
	string word;
	while (true) {
		getline(cin, word);
		word = toUpperCase(word);
		if (word.empty()) {
			return;
		} else if (!boggle.isCorrectFormat(word)) {
			cout << "Please type a word with at least 4 alpha characters: ";
		} else if (!boggle.isValidEnglishWord(word)) {
			cout << "Please type a valid English word: ";
		} else if (isAlreadyUsed(words, word)) {
			cout << "Please type a word that has not already been used: ";
		} else if (!boggle.isValidWord(word)) {
			cout << "Please type a word that can be made from the cubes: ";
		} else {
			boggle.addUserWord(word);
		}
	}
}

void printScore(unsigned int score) {
	cout << "Your score: " << score << endl;
}

void printWords(vector<string>& words, bool computer) {
	string fw;
	if (computer) fw = "My";
	else fw = "Your";
	int size = words.size();
	cout << fw << " words (" << size << "): {";
	for (int i = 0; i < size - 1; ++i) {
		cout << "\"" << words[i] << "\", ";
	}
	if (size != 0) {
		cout << "\"" << words.back() << "\"}" << endl;
	} else {
		cout << "}" << endl;
	}
}

void inputCustomSides(Boggle& boggle) {
	cout << "Enter 16 characters A-Z: " << endl;
	string ans;
	while (true) {
		cin >> ans;
		if (ans.length() != 16) {
			cout << "Please type a string of exactly 16 characters:" <<
			endl;
		} else if (!boggle.isAlpha(ans)){
			cout << "Please type a string with only characters from A-Z:" <<
			endl;
		} else break;
	}
	ans = toUpperCase(ans);
	boggle.insertCustomCubes(createSides(ans));
}

vector<string> createSides(string& ans) {
	vector<string> sides;
	sides.resize(NUM_CUBES);
	for (unsigned int i = 0; i < NUM_CUBES; ++i) {
		sides[i] = ans[i]; 
	}
	return sides;
}

bool isAlpha(string& text) {
	for (char c : text) {
		if (!isalpha(c)) return false;
	}
	return true;
}

bool randomBoard() {
	cout << "Do you want to generate a random board? (y/n): ";
	string ans;
	while (true) {
		cin >> ans;
		ans = trim(toLowerCase(ans));
        if (startsWith(ans, 'y')) {
            return true;
        } else if (startsWith(ans, 'n')) {
            return false;
        } else {
            cout << "Please type a word that begins with 'y' or 'n'." <<
			endl;
        }
	}
}

/*
 * Erases all currently visible text from the output console.
 */
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("CLS");
#else
    // assume POSIX
    std::system("clear");
#endif
}
