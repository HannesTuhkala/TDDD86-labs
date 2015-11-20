#include "Board.h"
#include "shuffle.h"

Board::Board(unsigned int size) {
	unsigned int sideIndex = 0;
	std::string cubeSides[16] = {        // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
	};
	cubes = Grid<Cube*>(size, size);
	for (unsigned int i = 0; i < size; ++i) {
		for (unsigned int j = 0; j < size; ++j) {
			cubes[i][j] = new Cube(cubeSides[sideIndex]);
			sideIndex++;
		}
	}
	this->size = size;
	shuffleBoard();
}

Board::~Board() {
	for (unsigned int i = 0; i < size; ++i) {
		for (unsigned int j = 0; j < size; ++j) {
			delete cubes[i][j];
		}
	}
}

void Board::shuffleBoard() const {
	shuffle(cubes); //kan inte shuffla pekare??
}

std::string Board::toString() const {
	std::string result = "";
	for (unsigned int i = 0; i < size; ++i) {
		for (unsigned int j = 0; j < size; ++j) {
			result += cubes[i][j]->sideUp();
			result += ' ';
		}
		result += "\n";
	}
	return result;
}

bool Board::isValid() const {
	//TODO implementera detta
	return true;
}

bool Board::isNeighbor(int index, char c) {
	//TODO implementera detta
	return true;
}

