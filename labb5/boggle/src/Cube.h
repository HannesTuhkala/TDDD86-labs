/*
* This is the datastructure för each cube
*/
#ifndef CUBE_H
#define CUBE_H
#include <string>

class Cube {
	public:
	/*
	Constructs a Cube with the sides of the given string
	 */
	Cube(std::string sides);
	/*
	Destroys a Cube
	*/
	~Cube();
	/*
	Returns the character of the side that is up.
	*/
	char sideUp() const;
	/*
	Selects a random side on the cube to be up.
	*/
	void shuffle();

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
	The number of sides.
	*/
	static const int SIDES = 6;
};

#endif
