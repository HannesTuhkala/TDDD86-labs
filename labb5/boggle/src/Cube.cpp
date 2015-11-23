#include "Cube.h"
#include "random.h"

Cube::Cube() {}

Cube::Cube(std::string sides) {
	this->sides = sides;
	shuffle();
}

void Cube::shuffle() {
	sideUpIndex = randomInteger(0, SIDES - 1);
}

char Cube::sideUp() const {
	return sides[sideUpIndex];
}
