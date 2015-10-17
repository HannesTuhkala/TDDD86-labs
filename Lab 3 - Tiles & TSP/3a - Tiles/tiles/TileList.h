#ifndef TILELIST_H
#define TILELIST_H

#include <QGraphicsScene>
#include "Tile.h"

/*
 * A list of Tiles. Tiles at the bottom of the list has the highest z-index while the Tiles at the top of the list has the lowest z-index.
*/
class TileList {
public:

    /*
     * Creates a new TileList and instantiates the private members.
    */
    TileList();

    /*
     * Deletes the array.
    */
    ~TileList();

    /*
     * Adds a tile to the bottom of the TileList (it gets the highest z-index).
    */
    void addTile(const Tile& tile);

    /*
     * Draws all the tiles in the TileList. Tiles at the top of the TileList appears at the bottom of the screen, while those at the bottom appears at the top of the screen.
    */
    void drawAll(QGraphicsScene* scene) const;

    /*
     * Returns the tile in the given position (x, y) that has the highest z-index (closest to the bottom of the TileList)
    */
    int indexOfTopTile(const int x, const int y) const;

    /*
     * Lowers the selected tile in the given position (x, y) to the top of the TileList (makes it the lowest z-index).
    */
    void lower(const int x, const int y);

    /*
     * Raises the selected tile to the bottom of the TileList (makes it the highest z-index).
    */
    void raise(const int x, const int y);

    /*
     * Removes the tile in the given position (x, y) with the highest z-index (the tile closest to the bottom of the TileList).
    */
    void remove(const int x, const int y);

    /*
     * Removes all of the tiles in the given position (x, y).
    */
    void removeAll(const int x, const int y);

private:
    /*
     * size tells how many Tiles there are in the TileList at the moment. Default size is '0'.
    */
    int size;

    /*
     * capacity tells how many elements the current TileList can hold at the moment and will increase by 2 everytime it gets full. Default capacity is '10'.
    */
    int capacity;

    /*
     * The array holding all the tiles -> Tiles to the top of the array has the lowest z-index and the tiles to the bottom of the array has the highest z-index.
    */
    Tile* tiles;

    /*
     * Expands the array to 2 * current capacity and returns the new array. It copies all the old elements as well.
    */
    Tile* expandArray(Tile*& oldArray);

    /*
     * Pushes all elements to the right of index one step to the left.
    */
    void pushElementsToLeft(const int index);
};

#endif // TILELIST_H
