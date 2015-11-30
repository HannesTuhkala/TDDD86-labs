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
void printWords(vector<string>& words);
vector<string> createSides(string& ans);
string enterWord(Boggle& boggle, Lexicon& dictionary, vector<string>& words);
void printScore(unsigned int score);
bool isAlpha(string& text);
bool randomBoard();
bool isCorrectFormat(string word);
bool isAlreadyUsed(vector<string>& words, string word);

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
	Lexicon dictionary("EnglishWords.dat");
	while (true) {
		printWords(words);
		printScore(score);
		string temp = enterWord(boggle, dictionary, words);
		if (temp.empty()) break;
		words.push_back(temp);
		cout << "You found a new word! \"" << temp << "\"" << endl;
	}
}

string enterWord(Boggle& boggle, Lexicon& dictionary, vector<string>& words) {
	cout << "Type a word (or press Enter to end your turn): ";
	string word;
	while (true) {
		getline(cin, word);
		word = toUpperCase(word);
		if (word.empty()) {
			return "";
		} else if (!isCorrectFormat(word)) {
			cout << "Please type a word with 4 alpha characters: ";
		} else if (!dictionary.contains(word)) {
			cout << "Please type a valid English word:";
		} else if (isAlreadyUsed(words, word)) {
			cout << "Please type a word that has not already been used:";
		} else if (/*om strängen inte går att bilda*/) {
			cout << "Please type a word that has not already been used:";
		} else {
			return word;
		}
	}
}

bool isAlreadyUsed(vector<string>& words, string word) {
	for (string w : words) {
		if (word == w) return true;
	}
	return false;
}

bool isCorrectFormat(string word) {
	return isAlpha(word) && word.size() == 4;
}

void printScore(unsigned int score) {
	cout << "Your score: " << score << endl;
}

void printWords(vector<string>& words) {
	string w;
	int size = words.size();
	for (int i = 0; i < size - 1; ++i) {
		w += "\"";
		w += words[i];
		w += "\", ";
	}
	w += "\"";
	w += words.back();
	w += "\"";
	cout << "Your words (" << size << "): {"
	<< w << "}" << endl;;
}

void inputCustomSides(Boggle& boggle) {
	cout << "Enter 16 characters A-Z: " << endl;
	string ans;
	while (true) {
		cin >> ans;
		if (ans.length() != 16) {
			cout << "Please type a string of exactly 16 characters:" <<
			endl;
		} else if (!isAlpha(ans)){
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
