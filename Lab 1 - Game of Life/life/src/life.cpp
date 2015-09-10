#include <iostream>
#include <fstream>

#include "grid.h"
#include "lifeutil.h"

using namespace std;

/*
 * Ska vi göra en header fil med alla dessa funktions definitioner istället? Tror det skulle se bättre ut.
 */
void greetUser();

void loadGrid(Grid<char>& grid);

void setGridSize(Grid<char>& grid, ifstream& input);

void loadGridContent(Grid<char>& grid, ifstream& input);

void printGrid(Grid<char>& grid);

void nextGeneration(Grid<char>& grid);

void printGrid(Grid<char>& grid);

bool isCellAlive(char cell);

int countAliveNeighbors(Grid<char>& grid, int row, int column);

bool enoughNeighborsToLive(Grid<char>& grid, int row, int column);

void nextGeneration(Grid<char>& grid);

void evolve(Grid<char>& grid, Grid<char> tempGrid);

bool shouldBeBorn(Grid<char>& grid, int row, int column);

bool shouldDie(Grid<char>& grid, int row, int column);

char askForCommand();

void animate(Grid<char>& grid);

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

void animate(Grid<char>& grid){
    while (true) {
        nextGeneration(grid);
        clearConsole();
        printGrid(grid);
        pause(100);
    }
}

char askForCommand(){
    cout << "a)nimate, t)ick, q)uit? ";
    char choice;
    cin >> choice;
    return choice;
}

void greetUser() {
    cout << "Welcome to the TDDD86 Game of Life," << endl
         << "a simulation of the lifecycle of a bacteria colony." << endl
         << "Cells (X) live and die by the following rules:" << endl
         << "  - A cell with 1 or fewer neighbors dies." << endl
         << "  - Locations with 2 neighbors remain stable." << endl
         << "  - Locations with 3 neighbors will create life." << endl
         << "  - A cell with 4 or more neighbors dies.\n" << endl;
}

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

void setGridSize(Grid<char>& grid, ifstream& input){
    int rows;
    int columns;
    input >> rows;
    input >> columns;
    grid.resize(rows, columns);
}

void loadGridContent(Grid<char>& grid, ifstream& input){
    string line;
    getline(input, line); //skip a line
    for (int row = 0; row < grid.numRows(); ++row) {
        getline(input, line);
        for (int column = 0; column < grid.numCols(); ++column) {
            grid.set(row, column, line[column]);
        }
    }
    //cout << grid.toString() << endl;
}

void printGrid(Grid<char>& grid) {
    for (int row = 0; row < grid.numRows(); ++row) {
        for (int column = 0; column < grid.numCols(); ++column) {
            cout << grid.get(row, column);
        }
        cout << endl;
    }
}

bool isCellAlive(char cell) {
    return cell == 'X';
}

bool shouldBeBorn(Grid<char>& grid, int row, int column) {
    return countAliveNeighbors(grid, row, column) == 3;
}

bool shouldDie(Grid<char>& grid, int row, int column) {
    int neighbors = countAliveNeighbors(grid, row, column);
    return neighbors > 3 || neighbors < 2;
}

int countAliveNeighbors(Grid<char>& grid, int row, int column) {
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



void setAlive(Grid<char>& grid, int row, int col, bool alive){
    if (alive){
        grid.set(row, col, 'X');
    } else {
        grid.set(row, col, '-');
    }
}

void nextGeneration(Grid<char>& grid) {
    Grid<char> temp = grid;
    evolve(grid, temp);
}

void evolve(Grid<char>& grid, Grid<char> tempGrid){
    for (int row = 0; row < grid.numRows(); ++row) {
        for (int column = 0; column < grid.numCols(); ++column) {
            if (!isCellAlive(tempGrid.get(row, column))) { // cell is dead
                if (shouldBeBorn(tempGrid, row, column)) {
                    setAlive(grid, row, column, true);
                }
            } else { // cell is alive
                if (shouldDie(tempGrid, row, column)) {
                    setAlive(grid, row, column, false);
                }
            }
        }
    }
}
