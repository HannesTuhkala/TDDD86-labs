/*
 * This file is part of an implementation of the Boggle game, by
 * Malcolm Vigren (malvi108) and Hannes Tuhkala (hantu447).
 */

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
void printWords(Boggle& boggle, bool computer);
void createSides(string& ans, vector<string>& sides);
void enterWord(Boggle& boggle);
void printScore(unsigned int score);
bool randomBoard();
unsigned int countComputerScore(vector<string> words);

/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle& boggle) {

	clearConsole();
	boggle.reset();

	if (randomBoard()) {
		boggle.setDefaultBoard();
	} else {
		inputCustomSides(boggle);
	}
	clearConsole();

	cout << "It's your turn!" << endl;
	cin.ignore();

	enterWord(boggle);
	// computer's turn
	cout << "It's my turn!" << endl;
	boggle.playComputerTurn();
	// cout << boggle.boardToString() << endl;
	printWords(boggle, true);
	unsigned int computerScore = boggle.getComputerScore();
	unsigned int userScore = boggle.getUserScore();
	cout << "My score: " << computerScore << endl;
	cout << "Your score: " << userScore << endl;
	if (computerScore > userScore) {
		cout << "Ha ha ha, I destroyed you. Better luck next time, puny human!" << endl;
	} else if (computerScore == userScore) {
		cout << "It's a tie!" << endl;
	} else {
		cout << "Holy crap! You actually won over me! Congrats!" << endl;
	}
}

void enterWord(Boggle& boggle) {
	while (true) {
		cout << boggle.boardToString() << endl;
		printWords(boggle, false);
		printScore(boggle.getUserScore());
		cout << "Type a word (or press Enter to end your turn): ";
		string word;
		getline(cin, word);
		word = toUpperCase(word);
		if (word.empty()) {
            cout << endl;
            return;
        }
		clearConsole();
		if (!boggle.isCorrectFormat(word)) {
			cout << "Please type a word with at least 4 alpha characters." << endl;
		} else if (!boggle.isValidEnglishWord(word)) {
			cout << "Please type a valid English word." << endl;
		} else if (boggle.isAlreadyUsed(word)) {
			cout << "Please type a word that has not already been used." << endl;
		} else if (!boggle.isValidWord(word)) {
			cout << "Please type a word that can be made from the cubes." << endl;
		} else {
			boggle.addUserWord(word);
			cout << "You found a new word! \"" << word << "\"" << endl;
		}
	}
}

void printScore(unsigned int score) {
	cout << "Your score: " << score << endl;
}

void printWords(Boggle& boggle, bool computer) {
	string fw;
	int size;
	if (computer) {
		fw = "My";
        size = boggle.computerWordsSize();
	}
	else { 
		fw = "Your";
        size = boggle.userWordsSize();
	}
	cout << fw << " words (" << size << "): {";
	for (int i = 0; i < size - 1; ++i) {
		cout << "\"" << boggle.wordAt(i, computer) << "\", ";
	}
	if (size != 0) {
		cout << "\"" << boggle.wordAt(size - 1, computer) << "\"}" << endl;
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
    vector<string> sides;
    createSides(ans, sides);
	boggle.insertCustomCubes(sides);
}

void createSides(string& ans, vector<string>& sides) {
	sides.resize(NUM_CUBES);
	for (unsigned int i = 0; i < NUM_CUBES; ++i) {
		sides[i] = ans[i]; 
	}
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
