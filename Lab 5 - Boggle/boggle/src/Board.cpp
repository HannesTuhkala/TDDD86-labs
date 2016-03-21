#include "Board.h"
#include "shuffle.h"

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const std::string DEFAULT_CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

Board::Board() {}

void Board::shuffleBoard() {
	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			cubes[i][j].shuffle();
		}
	}
	shuffle(cubes); 
}

void Board::setCubeSides(const std::vector<std::string>& sides) {
	cubes = Grid<Cube>(BOARD_SIZE, BOARD_SIZE);
	unsigned int sideIndex = 0;
	for (unsigned int i = 0; i < BOARD_SIZE; ++i) {
		for (unsigned int j = 0; j < BOARD_SIZE; ++j) {
			cubes[i][j] = Cube(sides[sideIndex]);
			sideIndex++;
		}
	}
}

void Board::setDefault() {
	cubes = Grid<Cube>(BOARD_SIZE, BOARD_SIZE);
	unsigned int sideIndex = 0;
	for (unsigned int i = 0; i < BOARD_SIZE; ++i) {
		for (unsigned int j = 0; j < BOARD_SIZE; ++j) {
			cubes[i][j] = Cube(DEFAULT_CUBES[sideIndex]);
			sideIndex++;
		}
	}
	shuffleBoard();
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
	std::vector<std::pair<int, int>> indices(row * col);
	for (int r = row - 1; r <= row + 1; ++r) {
		for (int c = col - 1; c <= col + 1; ++c) {
			if (cubes.inBounds(r, c)) {
				indices.push_back(pair<int,int>(r, c));
p			}
		}
	}
	for (auto index : indices) {
		if (cubes[index.first][index.second].sideUp() == c) return true;
	}
	return false;
}

void Board::setVisited(const int row, const int col, const bool aFlag) {
	cubes[row][col].setVisited(aFlag);
}

bool Board::isVisited(const int row, const int col) const {
	return cubes[row][col].isVisited();
}

char Board::cubeSideAt(const unsigned int row, const unsigned int col) const {
	return cubes[row][col].sideUp();
}

std::vector<std::pair<int,int>> Board::getNeighbors(int row, int col) const {
	std::vector<std::pair<int,int>> indices;
	for (int r = row - 1; r <= row + 1; ++r) {
		for (int c = col - 1; c <= col + 1; ++c) {
			if (cubes.inBounds(r, c)) {
				indices.push_back(std::pair<int,int>(r,c));
			}
		}
	}
	return indices;
}

std::vector<std::pair<int, int>> Board::getPossibleStartingPoints(char c) const {
	std::vector<std::pair<int,int>> indices;
	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			if (cubes[i][j].sideUp() == c) indices.push_back(pair<int,int>(i,j));
		}
	}
	return indices;
}

std::vector<std::pair<int,int>> Board::getAllStartingPoints() const {
	std::vector<std::pair<int,int>> indices;
	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			indices.push_back(pair<int,int>(i,j));
		}
	}
	return indices;
}
