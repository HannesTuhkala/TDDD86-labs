#include <iostream>
#include <fstream>

#include "grid.h"
#include "lifeutil.h"

using namespace std;

void greetUser();
void setGridSize(Grid<char>& grid, ifstream& input);
void loadGridContent(Grid<char>& grid, ifstream& input);
void loadGrid(Grid<char>& grid);
void printGrid(Grid<char>& grid);
void nextGeneration(Grid<char>& grid);
void evolve(Grid<char>& grid, Grid<char>& tempGrid);
void animate(Grid<char>& grid);
void setAlive(Grid<char>& grid, const int row, const int column, const bool alive);
bool isCellAlive(const char cell);
bool shouldBeBorn(const Grid<char>& grid, const int row, const int column);
bool shouldDie(const Grid<char>& grid, const int row, const int column);
int countAliveNeighbors(const Grid<char>& grid, const int row, const int column);
char askForCommand();

int main() {
    greetUser();
    Grid<char> grid = Grid<char>();
    loadGrid(grid);
    char decision;
    while(decision != 'q') {
        printGrid(grid);
        decision = askForCommand();
        if (decision == 'a') {
            animate(grid);
        } else if (decision == 't') {
            nextGeneration(grid);
        }
    }
    cout << "Have a nice Life!" << endl;
    return 0;
}

/*
 * Animates the grid to the console. Never stops so you have to use Ctrl + C to stop the program.
 */
void animate(Grid<char>& grid){
    while (true) {
        nextGeneration(grid);
        clearConsole();
        printGrid(grid);
        pause(100);
    }
}

/*
 * Asks the user for the different choices.
 */
char askForCommand(){
    cout << "a)nimate, t)ick, q)uit? ";
    char choice;
    cin >> choice;
    return choice;
}

/*
 * Greets the user with the default text.
 */
void greetUser() {
    cout << "Welcome to the TDDD86 Game of Life," << endl
         << "a simulation of the lifecycle of a bacteria colony." << endl
         << "Cells (X) live and die by the following rules:" << endl
         << "  - A cell with 1 or fewer neighbors dies." << endl
         << "  - Locations with 2 neighbors remain stable." << endl
         << "  - Locations with 3 neighbors will create life." << endl
         << "  - A cell with 4 or more neighbors dies.\n" << endl;
}

/*
 * Loads the grid based on the input file name.
 */
void loadGrid(Grid<char>& grid){
    ifstream input;
    cout << "Grid input file name? ";
    string file;
    cin >> file;
    input.open(file.c_str());

    setGridSize(grid, input);

    loadGridContent(grid, input);

    input.close();
}

/*
 * Changes the size of grid.
 */
void setGridSize(Grid<char>& grid, ifstream& input){
    int rows, columns;
    input >> rows;
    input >> columns;
    grid.resize(rows, columns);
}

/*
 *  Loads the actual file content into the grid
 */
void loadGridContent(Grid<char>& grid, ifstream& input){
    string line;
    getline(input, line); //skip a line
    for (int row = 0; row < grid.numRows(); ++row) {
        getline(input, line);
        for (int column = 0; column < grid.numCols(); ++column) {
            grid.set(row, column, line[column]);
        }
    }
}

/*
 * Prints the grids contents to the console.
 */
void printGrid(Grid<char>& grid) {
    for (int row = 0; row < grid.numRows(); ++row) {
        for (int column = 0; column < grid.numCols(); ++column) {
            cout << grid.get(row, column);
        }
        cout << endl;
    }
}

/*
 * Checks to see if a cell is alive. It is alive if it is equal to 'X'.
 */
bool isCellAlive(const char cell) {
    return cell == 'X';
}

/*
 * Checks to see if a cell should be born. It checks if the cell has atleast 3 alive neighbors.
 */
bool shouldBeBorn(const Grid<char>& grid, const int row, const int column) {
    return countAliveNeighbors(grid, row, column) == 3;
}

/*
 * Checks to see if a cell should die. It checks whether it has more than 3 neighbors (overpopulation) or less than 2.
 */
bool shouldDie(const Grid<char>& grid, const int row, const int column) {
    int neighbors = countAliveNeighbors(grid, row, column);
    return neighbors > 3 || neighbors < 2;
}

/*
 * Returns the amount of alive neighbors for a specific cell.
 */
int countAliveNeighbors(const Grid<char>& grid, const int row, const int column) {
    int neighbors = 0;

    for (int currentRow = row - 1; currentRow <= row + 1; ++currentRow) {
        for (int currentColumn = column - 1; currentColumn <= column + 1; ++currentColumn) {
            if (currentRow == row && currentColumn == column) {
                continue;
            }

            if (grid.inBounds(currentRow, currentColumn) && isCellAlive(grid.get(currentRow, currentColumn))) {
                neighbors += 1;
            }
        }
    }

    return neighbors;
}

/*
 * Sets the cell to alive or dead based on the bool alive.
 */
void setAlive(Grid<char>& grid, const int row, const int column, const bool alive) {
    if (alive){
        grid.set(row, column, 'X');
    } else {
        grid.set(row, column, '-');
    }
}

/*
 * Evolves to the next generation.
 */
void nextGeneration(Grid<char>& grid) {
    Grid<char> temp = grid;
    evolve(grid, temp);
}

/*
 * Function that evolves the grid to the next generation.
 */
void evolve(Grid<char>& grid, Grid<char>& tempGrid) {
    for (int row = 0; row < grid.numRows(); ++row) {
        for (int column = 0; column < grid.numCols(); ++column) {
            if (!isCellAlive(tempGrid.get(row, column))) {  // cell is dead
                if (shouldBeBorn(tempGrid, row, column)) {
                    setAlive(grid, row, column, true);
                }
            } else {                                        // cell is alive
                if (shouldDie(tempGrid, row, column)) {
                    setAlive(grid, row, column, false);
                }
            }
        }
    }
}
