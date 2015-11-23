#include "Board.h"
#include "shuffle.h"

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int BOARD_SIZE = 4;

Board::Board() {
	cubes = Grid<Cube>(BOARD_SIZE, BOARD_SIZE);
}

void Board::shuffleBoard() {
	for (Cube c : cubes) {
		c.shuffle();
	}
	shuffle(cubes); 
}

void Board::changeCubeSides(std::string* cubeSides) {
	unsigned int sideIndex = 0;
	for (unsigned int i = 0; i < BOARD_SIZE; ++i) {
		for (unsigned int j = 0; j < BOARD_SIZE; ++j) {
			cubes[i][j] = Cube(cubeSides[sideIndex]);
			sideIndex++;
		}
	}
}

std::string Board::toString() const {
	std::string result = "";
	for (unsigned int i = 0; i < BOARD_SIZE; ++i) {
		for (unsigned int j = 0; j < BOARD_SIZE; ++j) {
			result += cubes[i][j].sideUp();
			result += ' ';
		}
		result += "\n";
	}
	return result;
}

bool Board::isNeighbor(int row, int col, char c) const {
	vector<pair<int, int>> indices(row * col);
	for (int r = row - 1; r <= row + 1; ++r) {
		for (int c = col - 1; c <= col + 1; ++c) {
			if (cubes.inBounds(r, c)) {
				indices.push_back(pair<int,int>(r, c));
			}
		}
	}
	for (auto index : indices) {
		if (cubes[index.first][index.second].sideUp() == c) return true;
	}
	return false;
}

