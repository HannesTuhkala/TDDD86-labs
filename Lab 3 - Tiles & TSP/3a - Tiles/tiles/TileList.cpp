#include "TileList.h"

TileList::TileList()
{
	size = 0;
	capacity = 10;
	tiles = new Tile[capacity];
}

TileList::~TileList()
{
	delete[] tiles;
}

void TileList::addTile(const Tile& tile)
{
	if (size == capacity) {
		tiles = expandArray(tiles);
	} else {
		tiles[size] = tile;
		++size;
	}
}

Tile* TileList::expandArray(Tile*& oldArray) {
	capacity *= 2;
	Tile* newTiles = new Tile[capacity];
	for (int i = 0; i < size; ++i) { // since size = old capacity
		newTiles[i] = oldArray[i];
	}
	delete[] oldArray;
	return newTiles;
}

void TileList::drawAll(QGraphicsScene* scene) const
{
	for (int i = 0; i < size; ++i) {
		tiles[i].draw(scene);
	}
}

int TileList::indexOfTopTile(const int x, const int y) const
{
    for (int i = size - 1; i >= 0; --i) {
		if (tiles[i].contains(x, y)) {
			return i; 
		}
	}

	return -1;
}

void TileList::raise(const int x, const int y)
{
    int index = indexOfTopTile(x, y);
    if (index == -1) return;

    Tile tile = tiles[index];
    pushElementsToLeft(index);
    tiles[size - 1] = tile;
}

void TileList::pushElementsToLeft(const int index) {
    for (int i = index; i < size - 1; ++i) {
        tiles[i] = tiles[i + 1];
    }
}

void TileList::lower(const int x, const int y)
{
    int index = indexOfTopTile(x, y);
    if (index == -1) return;
    Tile tile = tiles[index];

    for (int i = index; i > 0; --i) {
        tiles[i] = tiles[i - 1];
    }

    tiles[0] = tile;
}

void TileList::remove(const int x, const int y)
{
	int index = indexOfTopTile(x, y);
	if (index == -1) return;
    pushElementsToLeft(index);
    --size;
}

void TileList::removeAll(const int x, const int y)
{
    while (indexOfTopTile(x, y) != -1) {
        remove(x, y);
    }
}
