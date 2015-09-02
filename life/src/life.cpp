#include <iostream>
#include <fstream>

#include "grid.h"
#include "lifeutil.h"
#include "strlib.h"

using namespace std;

// Skriver funktions definitionerna här uppe för att slippa ha main() funktionen längst ner i filen.
void printStart();
void printAfterGeneration();
void printEnd();
void readFile(string fileName, Grid<string>& routenet);

int main() {
    // TODO: Finish the program!

    Grid<string> grid;

    printStart();

    string fileName;
    cin >> fileName;
    readFile(fileName, grid);

    printAfterGeneration();

    return 0;
}

//MALCOLM: Det stod att han föredrog att man avslutade raden med endl; istället för \n fyi
void printStart() {
    cout << "Welcome to the TDDD86 Game of Life," << endl
         << "a simulation of the lifecycle of a bacteria colony." << endl
         << "Cells (X) live and die by the following rules:" << endl
         << " - A cell with 1 or fewer neighbours dies." << endl
         << " - Locations with 2 neighbours remain stable." << endl
         << " - Locations with 3 neighbours will create life." << endl
         << " - A cell with 4 or more neighbours dies." << endl << endl
         << "Grid input file name? ";
}

void printAfterGeneration() {
    cout << "a)nimate, t)ick, q)uit?" << endl;
}

void printEnd() {
    cout << "Have a nice Life!" << endl;
}


/*
 * stringToInteger och alla dess funktioner i strlib.cpp fungerar inte. Se om du kan få det att fungera. Kompilatorn klagar på "undefined reference to 'stringToInteger(std::string)'..
 */
void readFile(string fileName, Grid<string>& grid) {
    ifstream input;
    input.open(fileName);
    string line;
    string rows, columns;
    getline(input, line);
    //rows = stringToInteger(line);
    getline(input, line);
    //columns = stringToInteger(line);
    //grid.resize(rows, columns);
    cout << rows << " " << columns << endl;
}
