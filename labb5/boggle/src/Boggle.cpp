// This is the .cpp file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace it with your own

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"

static const int CUBE_SIDES = 6;   // the number of sides on each cube
static const std::string CUBE_SIDES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
/*"AAAAAA", "BBBBBB", "CCCCCC", "DDDDDD",
"EEEEEE", "FFFFFF", "GGGGGG", "HHHHHH",
"IIIIII", "JJJJJJ", "KKKKKK", "LLLLLL",
"MMMMMM", "NNNNNN", "OOOOOO", "PPPPPP"*/
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

Boggle::Boggle() {
	Board* board = new Board();
	board->changeCubeSides(CUBE_SIDES); //standard config
}

Boggle::~Board() {
	delete board;
}

void Boggle::shuffleBoard() {
	board->shuffleBoard();
}

void Boggle::insertCustomCubes(std::string* sides) {
	board->changeCubeSides(sides);
}

std::string Boggle::boardToString() const {
	return board->toString();
}

