#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"
#include "Board.h"
#include "Cube.h"
#include <cctype>

static const int NUM_CUBES = 16;

void clearConsole();
void playOneGame(Boggle& boggle);
void inputCustomSides(Boggle& boggle);
std::vector<string> createSides(std::string& ans);
bool isAlpha(std::string& text);
bool randomBoard();

/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle& boggle) {
	if (randomBoard()) {
		boggle.setDefaultBoard();
	} else {
		inputCustomSides(boggle);
	}
	// TODO not done yet
	// jag gillar glass
}

void inputCustomSides(Boggle& boggle) {
	std::cout << "Enter 16 characters A-Z: " << std::endl;
	std::string ans;
	while (true) {
		std::cin >> ans;
		if (ans.length() != 16) {
			std::cout << "Please type a string of exactly 16 characters:" <<
			std::endl;
		} else if (!isAlpha(ans)){
			std::cout << "Please type a string with only characters from A-Z:" <<
			std::endl;
		} else break;
	}
	ans = toUpperCase(ans);
	boggle.insertCustomCubes(createSides(ans));
}

std::vector<string> createSides(std::string& ans) {
	std::vector<string> sides;
	sides.resize(NUM_CUBES);
	for (unsigned int i = 0; i < NUM_CUBES; ++i) {
		sides[i] = ans[i]; 
	}
	return sides;
}

bool isAlpha(std::string& text) {
	for (char c : text) {
		if (!isalpha(c)) return false;
	}
	return true;
}

bool randomBoard() {
	std::cout << "Do you want to generate a random board? (y/n): ";
	std::string ans;
	while (true) {
		std::cin >> ans;
		ans = trim(toLowerCase(ans));
        if (startsWith(ans, 'y')) {
            return true;
        } else if (startsWith(ans, 'n')) {
            return false;
        } else {
            std::cout << "Please type a word that begins with 'y' or 'n'." <<
			std::endl;
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
