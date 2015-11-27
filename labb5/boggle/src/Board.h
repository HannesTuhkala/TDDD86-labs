/*
* This is the datastructure that describes a board object.
*/

#ifndef BOARD_H
#define BOARD_H
#include <string>
#include "grid.h"
#include "Cube.h"

class Board {
	public:
	/*
	Constructs a board.
	*/
	Board();
	/*
	Changes the sides of the cubes. Parameter sides must be 16 strings of 6
	characters each.
	*/
	void setCubeSides(const std::vector<std::string>& sides);
	/*
	Sets the cube sides to the default sides.
	*/
	void setDefault();
	/*
	Gets a string representation of the board.
	*/
	std::string toString() const;
	/*
	Checks whether the char given is a neighbor to the given index, or if it is
	equal to the char of the given index.
	*/
	bool isNeighbor(int row, int col, char c) const;
	private:
	/*
	Shuffles the board.
	*/
	void shuffleBoard();
	/*
	The cubes
	*/
	Grid<Cube> cubes;
};


#endif
