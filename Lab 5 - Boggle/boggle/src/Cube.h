/*
* This is the datastructure for each cube
*/
#ifndef CUBE_H
#define CUBE_H
#include <string>

class Cube {
	public:
	Cube();
	/*
	Constructs a Cube with the sides of the given string
	 */
	Cube(std::string sides);
	/*
	Returns the character of the side that is up.
	*/
	char sideUp() const;
	/*
	Selects a random side on the cube to be up.
	*/
	void shuffle();
	/*
	Sets a custom index to be the side facing up.
	*/
	void setSideUp(const unsigned int index);
	/*
	Sets visit status.
	*/
	void setVisited(const bool aFlag);
	/*
	Returns visit status
	*/
	bool isVisited() const;

	private:
	/*
	The characters on each side.
	*/
	std::string sides;
	/*
	The index of the side that is up.
	*/
	int sideUpIndex;
	/*
	Whether cube has been visited by backtracking algorithm. Default is false.
	*/
	bool visited;
	/*
	The number of sides.
	*/
	static const int SIDES = 6;
	
};

#endif
