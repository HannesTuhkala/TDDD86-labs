// This is the .cpp file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"

static const int CUBE_SIDES = 6;   // the number of sides on each cube

Boggle::Boggle() {}

void Boggle::setDefaultBoard() {
	board = Board();
	board.setDefault();
}

void Boggle::insertCustomCubes(const std::vector<string>& sides) {
	board = Board();
	board.setCubeSides(sides);
}

std::string Boggle::boardToString() const {
	return board.toString();
}
