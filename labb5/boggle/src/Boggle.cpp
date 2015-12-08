// This is the .cpp file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"

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

bool Boggle::isValidWord(const Lexicon& dict, string word) const {
//	int size = board.BOARD_SIZE;
//	for (int r = 0; r < size; ++r) {
//		for (int c = 0; c < size; ++c) {
//			Cube curr = board.cubeAt(r, c);
//			curr.setVisited(true);
//			vector<Cube> neighbors = board.getNeighbors(r, c);
//			for (Cube neighbor : neighbors) {
//				
//			}
//		}
//	}
	// du måste kolla alla grannar till c, markera den som besökt, rekursivt
	// anropa alla som inte är besökta och anda resultatet. typ
	//TODO implementera detta
	//skiten kompilerar iaf.
	//jag måste nog kolla baklänges NEJ!
	return checkValidWordHelp(dict, word, pair<int><int>(0,0));
}

//nej, du måste kolla från början av ordet till slutet, eftersom du måste
//kontrollera den mot lexiconet
//använd en stack för varje bokstav?
bool Boggle::checkValidWordHelp(const Lexicon& dict,
								string word,
								const pair<int><int> curr) const {
	if (word.empty()) return true;
	
}

