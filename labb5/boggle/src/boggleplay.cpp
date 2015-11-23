// You will edit and turn in this CPP file.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace with your own

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"
#include "Board.h"
#include "Cube.h"
// TODO: include any other header files you need

/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle& boggle) {
//	Board* board = new Board();
//	std::cout << board->toString() << std::endl;
//	std::cout << "Enter random character: ";
//	char c;
//	std::cin >> c;
//	std::cout << board->isNeighbor(3, 3, c) << std::endl;
//	delete board;
	
}

bool customInput() {
	std::cout << "Custom input? (y/n): ";
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
