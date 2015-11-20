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
	Board(unsigned int size);
	/*
	Destroys a board.
	*/
	~Board();
	/*
	Shuffles the board.
	*/
	void shuffleBoard() const;
	/*
	Gets a string representation of the board.
	*/
	std::string toString() const;
	/*
	Checks whether a given string is a valid word to enter.
	*/
	bool isValid() const;

	private:
	/*
	The cubes,
	*/
	Grid<Cube*> cubes;
	/*
	The size of the board.
	*/
	unsigned int size;
	/*
	Checks whether the char given is a neighbor to the given index.
	*/
	bool isNeighbor(int index, char c);
};


#endif
