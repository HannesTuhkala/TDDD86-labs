#include "Cube.h"
#include "random.h"

Cube::Cube() {}

Cube::Cube(std::string sides) {
	this->sides = sides;
	sideUpIndex = 0;
	visited = false;
}

void Cube::shuffle() {
	sideUpIndex = randomInteger(0, SIDES - 1);
}

char Cube::sideUp() const {
	return sides[sideUpIndex];
}

void Cube::setSideUp(const unsigned int index) {
	sideUpIndex = index;
}

void Cube::setVisited(const bool aFlag) {
	visited = aFlag;
}

bool Cube::isVisited() const {
	return visited;
}
